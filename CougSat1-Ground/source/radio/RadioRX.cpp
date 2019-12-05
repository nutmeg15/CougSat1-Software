#include "RadioRX.h"

#include <chrono>
#include <spdlog/spdlog.h>

#include <components/communications/IQSource/RTLSDR.h>
#include <components/communications/IQSource/WAV.h>

namespace Radio {

/**
 * @brief Destroy the RadioRX:: RadioRX object
 *
 */
RadioRX::~RadioRX() {
  stop();
  delete iqSource;
}

/**
 * @brief Initialize the Radio RX, create the IQSource
 *
 * @param guiBuf to plot to
 * @return Result
 */
Result RadioRX::init(CircularBuffer<PairDouble_t> * guiBuf) {
  gui = guiBuf;

  return ResultCode_t::SUCCESS;
}

/**
 * @brief Set a WAV file as the IQ source
 *
 * @param file to read
 * @return Result
 */
Result RadioRX::setIQFile(FILE * file) {
  // Reset file to start just to be sure
  if (fseek(file, 0L, SEEK_SET) != 0)
    return ResultCode_t::READ_FAULT + "Failed to rewind file";

  Communications::IQSource::IQSource * oldSource = iqSource;
  Communications::IQSource::WAV *      newSource =
      new Communications::IQSource::WAV(file);
  Result result = newSource->init();
  if (!result)
    return result + "Failed to initialize WAV Source";

  iqSource = newSource;
  delete oldSource;

  return ResultCode_t::SUCCESS;
}

/**
 * @brief Set a RTL SDR dongle as the IQ source
 *
 * @param centerFreq
 * @return Result
 */
Result RadioRX::setRTLSDR(const uint32_t centerFreq) {
  Communications::IQSource::IQSource * oldSource = iqSource;
  Communications::IQSource::RTLSDR *   newSource =
      new Communications::IQSource::RTLSDR(centerFreq);
  Result result = newSource->init();
  if (!result)
    return result + "Failed to initialize RTL SDR Source";

  iqSource = newSource;
  delete oldSource;

  return ResultCode_t::SUCCESS;
}

/**
 * @brief Start the RadioRX loop
 *
 */
void RadioRX::start() {
  stop();
  running = true;
  thread  = new std::thread(&RadioRX::run, this);
}

/**
 * @brief Stop the RadioRX loop
 *
 */
void RadioRX::stop() {
  running = false;
  if (thread == nullptr)
    return;
  if (thread->joinable())
    thread->join();
  delete thread;
  thread = nullptr;
}

/**
 * @brief Run the RadioRX loop, listen for signals
 *
 */
void RadioRX::run() {
  int16_t      i;
  int16_t      q;
  ResultCode_t result;
  while (running) {
    if (iqSource != nullptr) {
      result = iqSource->getIQ(i, q);
      if (result == ResultCode_t::BUFFER_OVERFLOW) {
        // IQ buffer is empty, remove the source
        i = 0;
        q = 0;
        // delete iqSource;
        // iqSource = nullptr;
      } else if (!result) {
        spdlog::error((result + "Failed to get IQ").getMessage());
        running = false;
        return;
      }
      // spdlog::info("{} {}", i, q);
      while (running && !gui->push({i / 32768.0, q / 32768.0}))
        std::this_thread::sleep_for(millis_t(1));
      // std::this_thread::sleep_for(millis_t(1));
    } else
      std::this_thread::sleep_for(millis_t(10));
  }
}

} // namespace Radio