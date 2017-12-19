//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
// Cleaver - A MultiMaterial Conforming Tetrahedral Meshing Library
//
// -- Utilities
//
// Author: Jonathan Bronson (bronson@sci.utah.ed)
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//  Copyright (C) 2011, 2012, Jonathan Bronson
//  Scientific Computing & Imaging Institute
//  University of Utah
//
//  Permission is  hereby  granted, free  of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files  ( the "Software" ),  to  deal in  the  Software without
//  restriction, including  without limitation the rights to  use,
//  copy, modify,  merge, publish, distribute, sublicense,  and/or
//  sell copies of the Software, and to permit persons to whom the
//  Software is  furnished  to do  so,  subject  to  the following
//  conditions:
//
//  The above  copyright notice  and  this permission notice shall
//  be included  in  all copies  or  substantial  portions  of the
//  Software.
//
//  THE SOFTWARE IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY  OF ANY
//  KIND,  EXPRESS OR IMPLIED, INCLUDING  BUT NOT  LIMITED  TO THE
//  WARRANTIES   OF  MERCHANTABILITY,  FITNESS  FOR  A  PARTICULAR
//  PURPOSE AND NONINFRINGEMENT. IN NO EVENT  SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS  BE  LIABLE FOR  ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//  USE OR OTHER DEALINGS IN THE SOFTWARE.
//-------------------------------------------------------------------
//-------------------------------------------------------------------

#include "Util.h"
#include <cmath>

using namespace std;

namespace cleaver
{


//-------------------------------------------------------------------
//  pow2() method
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
// Original Author: Adam Bargteil (adamb@cs.berkeley.edu)
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
// Copyright (c) 2003-2005, Regents of the University of California.  All
// rights reserved.
//
// This software is part of the Berkeley Fluid Animation & Simulation
// Toolkit.  The name "Berkeley Fluid Animation & Simulation Toolkit" is
// a trademark of the Regents of the University of California.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//   Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the distribution.
//
//  Redistributions in binary form as an executable program, or part of
//  an executable program must, when run for the first time by a given
//  user, prominently display the above copyright notice, this list of
//  conditions and the following disclaimer.
//
//  Neither the name of the University of California, Berkeley nor the
//  names of its contributors may be used to endorse or promote products
//  derived from this software without specific prior written
//  permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------
double pow2(int p) {
  switch (p) {
    case -20: return 9.53674e-07;
    case -19: return 1.90735e-06;
    case -18: return 3.8147e-06;
    case -17: return 7.62939e-06;
    case -16: return 1.52588e-05;
    case -15: return 3.05176e-05;
    case -14: return 6.10352e-05;
    case -13: return 0.0001220703125;
    case -12: return 0.000244140625;
    case -11: return 0.00048828125;
    case -10: return 0.0009765625;
    case -9: return 0.001953125;
    case -8: return 0.00390625;
    case -7: return 0.0078125;
    case -6: return 0.015625;
    case -5: return 0.03125;
    case -4: return 0.0625;
    case -3: return 0.125;
    case -2: return 0.25;
    case -1: return 0.5;
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    case 4: return 16;
    case 5: return 32;
    case 6: return 64;
    case 7: return 128;
    case 8: return 256;
    case 9: return 512;
    case 10: return 1024;
    case 11: return 2048;
    case 12: return 4096;
    case 13: return 8192;
    case 14: return 16384;
    case 15: return 32768;
    case 16: return 65536;
    case 17: return 131072;
    case 18: return 262144;
    case 19: return 524288;
    case 20: return 1048576;
  default:
    double ret = 1;
    if (abs(p) == p)
      for (int i=0; i<abs(p); i++)
                ret *= 2.0;
    else
      for (int i=0; i<abs(p); i++)
                ret /= 2.0;
    return ret;
  }
}


//--------------------------------------------------------------------------------------------
//  triangle_intersect()
//
//  This method computes the intersection of a ray and triangle. The intersection point
//  is stored in 'pt', while a boolean returned indicates whether or not the intersection
//  occurred in the triangle. Epsilon tolerance is given to boundary case.
//--------------------------------------------------------------------------------------------
bool triangle_intersection(Vertex *v1, Vertex *v2, Vertex *v3, vec3 origin, vec3 ray, vec3 &pt, float epsilon)
{
    float epsilon2 = (float)1E-3;

    //-------------------------------------------------
    // if v1, v2, and v3 are not unique, return FALSE
    //-------------------------------------------------
    if (v1 == v2 || v2 == v3 || v1 == v3)
      return false;
    else if (L2(v1->pos() - v2->pos()) < epsilon || L2(v2->pos() - v3->pos()) < epsilon || L2(v1->pos() - v3->pos()) < epsilon)
      return false;

    //----------------------------------------------
    // compute intersection with plane, store in pt
    //----------------------------------------------
    vec3 e1 = v1->pos() - v3->pos();
    vec3 e2 = v2->pos() - v3->pos();

    ray = normalize(ray);
    vec3 r1 = ray.cross(e2);
    double denom = e1.dot(r1);

    if (fabs(denom) < epsilon)
      return false;

    double inv_denom = 1.0 / denom;
    vec3 s = origin - v3->pos();
    double b1 = s.dot(r1) * inv_denom;

    if (b1 < (0.0 - epsilon2) || b1 >(1.0 + epsilon2))
      return false;

    vec3 r2 = s.cross(e1);
    double b2 = ray.dot(r2) * inv_denom;

    if (b2 < (0.0 - epsilon2) || (b1 + b2) >(1.0 + 2 * epsilon2))
      return false;

    double t = e2.dot(r2) * inv_denom;
    pt = origin + t*ray;


    if (t < 0.01)
      return false;
    else
      return true;
}


//-------------------------------------------------------------------
// vertex_to_json()
//-------------------------------------------------------------------
// Creats a json representation of the Vertex in its current state.
// This captures the position and material value of the vertex.
//-------------------------------------------------------------------
Json::Value vertex_to_json(Vertex *vertex) {
  Json::Value root(Json::objectValue);
  root["id"] = vertex->tm_v_index;
  root["material"] = vertex->label;
  root["position"] = Json::Value(Json::objectValue);
  root["position"]["x"] = vertex->pos().x;
  root["position"]["y"] = vertex->pos().y;
  root["position"]["z"] = vertex->pos().z;
  return root;
}

//-------------------------------------------------------------------
// tet_to_json()
//-------------------------------------------------------------------
// Creats a json representation of the Tet in its current state.
// All values, vertices and interfaces, are captured at the time of
// this function call. Mesh object requred for adjacency information.
//-------------------------------------------------------------------
Json::Value tet_to_json(Tet *tet, TetMesh *mesh, bool includeInterfaces) {
    
  Json::Value root(Json::objectValue);
  root["id"] = tet->tm_index;
  root["verts"] = Json::Value(Json::arrayValue);
  for (int v = 0; v < VERTS_PER_TET; v++) {
    root["verts"].append(vertex_to_json(tet->verts[v]));
  }

  // TODO(jonbronson): Be smarter about how to record virtual interfaces
  if (includeInterfaces) {
    Vertex *verts[4];
    HalfEdge *edges[6];
    HalfFace *faces[4];
    mesh->getAdjacencyListsForTet(tet, verts, edges, faces);

    root["cuts"] = Json::Value(Json::arrayValue);
    for (int e = 0; e < EDGES_PER_TET; e++) {
      root["cuts"].append(vertex_to_json(edges[e]->cut));
    }

    root["triples"] = Json::Value(Json::arrayValue);
    for (int f = 0; f < 4; f++) {
      root["triples"].append(vertex_to_json(faces[f]->triple));
    }

    root["quadruple"] = vertex_to_json(tet->quadruple);
  }
  return root;
}


} // namespace cleaver
