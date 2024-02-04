#pragma once
#include <ArduinoJson.h>

#include "Types/EffectUnit/EffectUnit.h"
#include "definitions.h"

class Effect{
  public:
    EffectUnit* keyColors;
    uint8_t size;
    Effect(){}
    Effect(uint8_t size);
    Effect(EffectUnit* effectUnit,uint8_t size);
    Effect(JsonDocument &doc);
    void addKeyColor(EffectUnit effectUnit, uint8_t position);
    ~Effect();
  private:
    static Effect parseCustomEffectFromJSON(JsonDocument &doc);
};