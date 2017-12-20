#ifndef OCTREEMESHER_H
#define OCTREEMESHER_H

#include "AbstractScalarField.h"
#include "TetMesh.h"

namespace cleaver2 {

class OctreeMesherImp;

class OctreeMesher
{
public:
    OctreeMesher(const cleaver2::AbstractScalarField *sizing_field = nullptr);
    ~OctreeMesher();

    void setSizingField(const cleaver2::AbstractScalarField *sizing_field);

    void createMesh();

    cleaver2::TetMesh* getMesh();

private:

    OctreeMesherImp *m_pimpl;
};

}

#endif // OCTREEMESHER_H
