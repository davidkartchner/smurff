#include "NoiseConfig.h"

#include <string>
#include <set>

#include <SmurffCpp/Utils/utils.h>

using namespace smurff;

#define NOISE_NAME_FIXED "fixed"
#define NOISE_NAME_ADAPTIVE "adaptive"
#define NOISE_NAME_PROBIT "probit"
#define NOISE_NAME_NOISELESS "noiseless"
#define NOISE_NAME_UNUSED "unused"

NoiseTypes smurff::stringToNoiseType(std::string name)
{
   if(name == NOISE_NAME_FIXED)
      return NoiseTypes::fixed;
   else if(name == NOISE_NAME_ADAPTIVE)
      return NoiseTypes::adaptive;
   else if(name == NOISE_NAME_PROBIT)
      return NoiseTypes::probit;
   else if(name == NOISE_NAME_NOISELESS)
      return NoiseTypes::noiseless;
   else if(name == NOISE_NAME_UNUSED)
      return NoiseTypes::unused;
   else
      throw std::runtime_error("Invalid noise type " + name);
}

std::string smurff::noiseTypeToString(NoiseTypes type)
{
   switch(type)
   {
      case NoiseTypes::fixed:
         return NOISE_NAME_FIXED;
      case NoiseTypes::adaptive:
         return NOISE_NAME_ADAPTIVE;
      case NoiseTypes::probit:
         return NOISE_NAME_PROBIT;
      case NoiseTypes::noiseless:
         return NOISE_NAME_NOISELESS;
      case NoiseTypes::unused:
         return NOISE_NAME_UNUSED;
      default:
         throw std::runtime_error("Invalid noise type");
   }
}

bool NoiseConfig::validate(bool throw_error) const 
{
   // AGE: here was a code that validated name field
   // but we dont need it now because we use enums and parsing functions that throw error

   return true;
}