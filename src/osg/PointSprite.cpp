/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2005 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 */
 
#include <osg/GLExtensions>
#include <osg/GL>
#include <osg/PointSprite>
#include <osg/State>
#include <osg/buffered_value>

using namespace osg;

int PointSprite::compare(const StateAttribute& sa) const
{
    if (this==&sa) return 0;\
    const std::type_info* type_lhs = &typeid(*this);\
    const std::type_info* type_rhs = &typeid(sa);\
    if (type_lhs->before(*type_rhs)) return -1;\
    if (*type_lhs != *type_rhs) return 1;\

    return 0; // passed all the above comparison macro's, must be equal.
}

void PointSprite::apply(osg::State& state) const
{
    if(!isPointSpriteSupported(state.getContextID())) return;

    glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, 1);
}

struct IntializedSupportedPair
{
    IntializedSupportedPair():
        initialized(false),
        supported(false) {}

    bool initialized;
    bool supported;
};

typedef osg::buffered_object< IntializedSupportedPair > BufferedExtensions;
static BufferedExtensions s_extensions;

bool PointSprite::isPointSpriteSupported(unsigned int contextID)
{
    if (!s_extensions[contextID].initialized)
    {
        s_extensions[contextID].initialized = true;
        s_extensions[contextID].supported = isGLExtensionSupported(contextID, "GL_ARB_point_sprite") || isGLExtensionSupported(contextID, "GL_NV_point_sprite");
    }

    return s_extensions[contextID].supported;
}
