//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Deals with singleton  
//
// $Revision: $
// $NoKeywords: $
//=============================================================================//

#if !defined( DETAILOBJECTSYSTEM_H )
#define DETAILOBJECTSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "igamesystem.h"
#include "icliententityinternal.h"
#include "engine/ivmodelrender.h"
#include "mathlib/vector.h"
#include "ivrenderview.h"

struct model_t;

#if defined ( SWARM_DLL )

struct WorldListLeafData_t;	
struct DistanceFadeInfo_t;

//-----------------------------------------------------------------------------
// Info used when building lists of detail objects to render
//-----------------------------------------------------------------------------
struct DetailRenderableInfo_t
{
	IClientRenderable *m_pRenderable;
	int m_nLeafIndex;
	RenderGroup_t m_nRenderGroup;
	RenderableInstance_t m_InstanceData;
};

typedef CUtlVectorFixedGrowable< DetailRenderableInfo_t, 2048 > DetailRenderableList_t;

#endif // SWARM_DLL


//-----------------------------------------------------------------------------
// Responsible for managing detail objects
//-----------------------------------------------------------------------------
abstract_class IDetailObjectSystem : public IGameSystem
{
public:
#if defined ( SWARM_DLL )
	// How many detail models (as opposed to sprites) are there in the level?
	virtual int GetDetailModelCount() const = 0;

	// Computes the detail prop fade info
	virtual float ComputeDetailFadeInfo( DistanceFadeInfo_t *pInfo ) = 0;

	// Builds a list of renderable info for all detail objects to render
	virtual void BuildRenderingData( DetailRenderableList_t &list, const SetupRenderInfo_t &info, float flDetailDist, const DistanceFadeInfo_t &fadeInfo ) = 0;
#endif

    // Gets a particular detail object
	virtual IClientRenderable* GetDetailModel( int idx ) = 0;

	// Gets called each view
	virtual void BuildDetailObjectRenderLists( const Vector &vViewOrigin ) = 0;

	// Renders all opaque detail objects in a particular set of leaves
	virtual void RenderOpaqueDetailObjects( int nLeafCount, LeafIndex_t *pLeafList ) = 0;

	// Call this before rendering translucent detail objects
	virtual void BeginTranslucentDetailRendering( ) = 0;

	// Renders all translucent detail objects in a particular set of leaves
	virtual void RenderTranslucentDetailObjects( const Vector &viewOrigin, const Vector &viewForward, const Vector &viewRight, const Vector &viewUp, int nLeafCount, LeafIndex_t *pLeafList ) =0;

	// Renders all translucent detail objects in a particular leaf up to a particular point
	virtual void RenderTranslucentDetailObjectsInLeaf( const Vector &viewOrigin, const Vector &viewForward, const Vector &viewRight, const Vector &viewUp, int nLeaf, const Vector *pVecClosestPoint ) = 0;
};


//-----------------------------------------------------------------------------
// System for dealing with detail objects
//-----------------------------------------------------------------------------
#if !defined ( SWARM_DLL )
IDetailObjectSystem* DetailObjectSystem();
#else
extern IDetailObjectSystem *g_pDetailObjectSystem;
inline IDetailObjectSystem* DetailObjectSystem()
{
	return g_pDetailObjectSystem;
}
#endif


#endif // DETAILOBJECTSYSTEM_H

