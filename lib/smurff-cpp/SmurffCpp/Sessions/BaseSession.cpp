#include "BaseSession.h"

#include <SmurffCpp/Priors/ILatentPrior.h>

using namespace smurff;

void BaseSession::addPrior(std::shared_ptr<ILatentPrior> prior)
{
   prior->setMode(m_priors.size());
   m_priors.push_back(prior);
}

void BaseSession::step() 
{
   for(auto &p : m_priors) 
      p->sample_latents();
   data()->update(m_model);
}

std::ostream &BaseSession::info(std::ostream &os, std::string indent) 
{
   os << indent << name << " {\n";
   os << indent << "  Data: {\n";
   data()->info(os, indent + "    ");
   os << indent << "  }\n";
   os << indent << "  Model: {\n";
   m_model.info(os, indent + "    ");
   os << indent << "  }\n";
   os << indent << "  Priors: {\n";
   for( auto &p : m_priors) 
      p->info(os, indent + "    ");
   os << indent << "  }\n";
   os << indent << "  Result: {\n";
   
   m_pred.info(os, indent + "    ");
   
   os << indent << "  }\n";
   return os;
}

void BaseSession::save(std::string prefix, std::string suffix) 
{
   m_model.save(prefix, suffix);
   m_pred.save(prefix);
   for(auto &p : m_priors) 
      p->save(prefix, suffix);
}

void BaseSession::restore(std::string prefix, std::string suffix) 
{
   m_model.restore(prefix, suffix);
   for(auto &p : m_priors) 
      p->restore(prefix, suffix);
}
