#pragma once

#include <string>

#define NOISE_NAME_FIXED "fixed"
#define NOISE_NAME_ADAPTIVE "adaptive"
#define NOISE_NAME_PROBIT "probit"
#define NOISE_NAME_NOISELESS "noiseless"
#define NOISE_NAME_UNUSED "unused"

namespace smurff
{
   enum class NoiseTypes
   {
      fixed,
      adaptive,
      probit,
      noiseless,
      unused,
   };

   NoiseTypes stringToNoiseType(std::string name);
   
   std::string noiseTypeToString(NoiseTypes type);

   class NoiseConfig
   {
   public:
      int cccc;
      
      // for fixed gaussian noise
      double precision  = 5.0;
   
      // for adaptive gausssian noise
      double sn_init    = 1.0;
      double sn_max     = 10.0;

   private:
      NoiseTypes m_noise_type;

   public:
      NoiseConfig(NoiseTypes nt = NoiseTypes::noiseless) 
         : m_noise_type(nt)
      {
         static int c = 0;
         c++;
         cccc = c;
      }

      //NoiseConfig(double p) : name("fixed"), precision(p) {}
      //NoiseConfig(double i, double m) : name("adaptive"), sn_init(i), sn_max(m) {}

   public:
      bool validate(bool = true) const;

   public:
      NoiseTypes getNoiseType() const
      {
         return m_noise_type;
      }

      void setNoiseType(NoiseTypes value)
      {
         m_noise_type = value;
      }
   };
}