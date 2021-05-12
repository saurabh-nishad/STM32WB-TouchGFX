/**
******************************************************************************
* File Name : TouchGFXConfiguration.cpp
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
* All rights reserved.</center></h2>
*
* This software component is licensed by ST under Ultimate Liberty license
* SLA0044, the "License"; You may not use this file except in compliance with
* the License. You may obtain a copy of the License at:
* www.st.com/SLA0044
*
******************************************************************************
*/
#include <texts/TypedTextDatabase.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <BitmapDatabase.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <TouchGFXHAL.hpp>
#include <STM32TouchController.hpp>
#include <stm32wbxx_hal.h>

extern "C" void touchgfx_init();
extern "C" void touchgfx_taskEntry();

static STM32TouchController tc;
static NoDMA dma;
static LCD16bpp display;
static ApplicationFontProvider fontProvider;
static Texts texts;
static TouchGFXHAL hal(dma, display, tc, 240, 320);

void touchgfx_init()
{
  Bitmap::registerBitmapDatabase(BitmapDatabase::getInstance(), BitmapDatabase::getInstanceSize());
  TypedText::registerTexts(&texts);
  Texts::setLanguage(0);

  FontManager::setFontProvider(&fontProvider);

  FrontendHeap& heap = FrontendHeap::getInstance();
  /*
   * we need to obtain the reference above to initialize the frontend heap.
   */
  (void)heap;

  /*
   * Initialize TouchGFX
   */
  hal.initialize();
}

void touchgfx_taskEntry()
{
 /*
  * Main event loop will check for VSYNC signal, and then process next frame.
  *
  * Note This function returns immediately if there is no VSYNC signal.
  */
  if (OSWrappers::isVSyncAvailable())
  {
    hal.backPorchExited();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
