#include "framework.h"
#include "node.h"
#include "shell.h"


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_darwin_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void aura_darwin_factory(::factory::factory * pfactory)
{

   aura_posix_factory(pfactory);

   apex_darwin_factory(pfactory);

}



