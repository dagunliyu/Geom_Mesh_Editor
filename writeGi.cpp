//! seriliation
using VectorInt = std::vector<int>;
using VectorDouble = std::vector<double>;

template<class _Vec>
void exportVecDat(const _Vec& vec, ofstream& os)
{
    size_t sFSize = vec.size();
    for (int sfIdx = 0; sfIdx < sFSize; ++sfIdx)
    {
        os << vec[sfIdx] << " ";
    }
    os << "\n";
}

bool serializeRegion(/*Base::Writer& writer, */RegionGeometry*& _geomRegion, const std::string& path)
{
    auto lamb_exportSurfRegion = [&](std::vector<mesh_cm::SurfaceRegion>& surfaces, ofstream& os)
    {
        size_t surfSize = surfaces.size();
        os << "surfaces " << surfSize << "\n";
        for (int surfRegIdx = 0; surfRegIdx < surfSize; ++surfRegIdx)
        {
            const auto& crSurf = surfaces[surfRegIdx];
            os << "SurfReg" << surfRegIdx << ":\n";

            os << "nodes " << crSurf.nodes.size() << "\n";
            for (auto& crNode : crSurf.nodes)
            {
                os << crNode << " ";
            }
            os << "\n";

            os << "normal: " << crSurf.normal[0] << " " << crSurf.normal[1] << " " << crSurf.normal[2] << "\n";

            os << "solidID: " << crSurf.solidID << " faceID: " << crSurf.faceID << " contact: " << crSurf.contact
                << " radiation: " << crSurf.radiation << " resistance: " << crSurf.resistance << " subdivided: " << crSurf.subdivided << "\n";
        }
        os << "\n";
    };

    auto lamb_exportVolumeRegion = [&](std::vector<mesh_cm::VolumeRegion>& volumes, ofstream& os)
    {
        size_t volSize = volumes.size();
        os << "Volumes " << volSize << "\n";
        int volIdx = 0;
        for (auto& crVolRegion : _geomRegion->volumes)
        {
            os << "VolumeRegion" << volIdx << ":" << "\n";
            //! range
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crVolRegion.range[rIdx] << " ";
            }
            os << "\n";
            //! meshSize
            os << "meshSize: ";
            for (int rIdx = 0; rIdx < 3; ++rIdx)
            {
                os << crVolRegion.meshSize[rIdx] << " ";
            }
            os << "\n";

            ++volIdx;
        }
        os << "\n";
    };

    auto lamb_exportPatchRegion = [&](std::vector<mesh_cm::PatchRegion>& patches, ofstream& os)
    {
        size_t pSize = patches.size();
        os << "patches " << pSize << "\n";
        int patchIdx = 0;
        for (auto& crPatchRegion : patches)
        {
            os << "PatchRegion" << patchIdx << ":\n";
            os << "name: " << crPatchRegion.name << "\n";
            os << "type: " << crPatchRegion.type << "\n";

            //! SurfaceRegion        
            lamb_exportSurfRegion(crPatchRegion.surfaces, os);

            ++patchIdx;
        }
        os << "\n";
    };

    auto lamb_exportZoneRegion = [&](std::vector<mesh_cm::ZoneRegion>& zones, ofstream& os)
    {
        size_t pSize = zones.size();
        os << "zones " << pSize << "\n";
        int zoneIdx = 0;
        for (auto& crZoneRegion : zones)
        {
            os << "ZoneRegion" << zoneIdx << ":\n";
            os << "name: " << crZoneRegion.name << "\n";
            os << "method: " << crZoneRegion.method << "\n";

            //! SurfaceRegion        
            lamb_exportSurfRegion(crZoneRegion.surfaces, os);

            ++zoneIdx;
        }
        os << "\n";
    };

    auto lamb_exportSizeRegion = [&](std::vector<mesh_cm::SizeRegion>& sizes, ofstream& os)
    {
        size_t sSize = sizes.size();
        os << "sizes " << sSize << "\n";
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            const auto& crSizeRegion = sizes[sIdx];
            os << "SizeRegion" << sIdx << ":\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crSizeRegion.range[rIdx] << " ";
            }
            os << "\n";
            os << "size: " << crSizeRegion.size[0] << " " << crSizeRegion.size[1] << " " << crSizeRegion.size[2] << "\n";
            os << "loExt: " << crSizeRegion.loExt[0] << " " << crSizeRegion.loExt[1] << " " << crSizeRegion.loExt[2] << "\n";
            os << "loExtSize: " << crSizeRegion.loExtSize[0] << " " << crSizeRegion.loExtSize[1] << " " << crSizeRegion.loExtSize[2] << "\n";
            os << "hiExt: " << crSizeRegion.hiExt[0] << " " << crSizeRegion.hiExt[1] << " " << crSizeRegion.hiExt[2] << "\n";
            os << "hiExtSize: " << crSizeRegion.hiExtSize[0] << " " << crSizeRegion.hiExtSize[1] << " " << crSizeRegion.hiExtSize[2] << "\n";
        }
        os << "\n";
    };

    auto lamb_exportCellSets = [&](std::vector<mesh_cm::CellSetRegion>& cellSets, ofstream& os)
    {
        size_t sSize = cellSets.size();
        os << "cellSets " << sSize << "\n";
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            const auto& crCellSetRegion = cellSets[sIdx];
            os << "CellSetRegion" << sIdx << ":\n";
            os << "name: " << crCellSetRegion.name << "\n";
            os << "method: " << crCellSetRegion.method << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crCellSetRegion.range[rIdx] << " ";
            }
            os << "\n";

            os << "dir: " << crCellSetRegion.direction << " solidID: " << crCellSetRegion.solidID << "\n";
        }
        os << "\n";
    };

    auto lamb_exportFaceSets = [&](std::vector<mesh_cm::FaceSetRegion>& faceSets, ofstream& os)
    {
        size_t sSize = faceSets.size();
        os << "faceSets " << sSize << "\n";
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            const auto& crFaceSetRegion = faceSets[sIdx];
            os << "FaceSetRegion" << sIdx << ":\n";
            os << "name: " << crFaceSetRegion.name << "\n";
            os << "method: " << crFaceSetRegion.method << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crFaceSetRegion.range[rIdx] << " ";
            }
            os << "\n";

            os << "normal: " << crFaceSetRegion.normal << "\n";
        }
        os << "\n";
    };

    auto lamb_exportFluidMarkers = [&](std::vector<mesh_cm::MarkerRegion>& fluidMarkers, ofstream& os)
    {
        size_t sSize = fluidMarkers.size();
        os << "fluidMarkers " << sSize << "\n";
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            const auto& crMarkerRegion = fluidMarkers[sIdx];
            os << "MarkerRegion" << sIdx << ":\n";
            os << "name: " << crMarkerRegion.name << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crMarkerRegion.range[rIdx] << " ";
            }
            os << "\n";
        }
        os << "\n";
    };

    auto lamb_exportDomainRegion = [&](std::vector<mesh_cm::DomainRegion>& domains, ofstream& os)
    {
        size_t sSize = domains.size();
        os << "domains " << sSize << "\n";
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            const auto& crDomainRegion = domains[sIdx];
            os << "DomainRegion" << sIdx << ":\n";
            os << "name: " << crDomainRegion.name << "\n";
            os << "type: " << crDomainRegion.type << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crDomainRegion.range[rIdx] << " ";
            }
            os << "\n";
        }
        os << "\n";
    };

    ofstream os; //Base::FileInfo fi(path.c_str()); Base::ofstream os(fi);
    os.open(path.c_str(), ios::out | ios::trunc);
    os << fixed;
    os << std::setprecision(20);
    os.setf(ios_base::showpoint);

    //! VolumeRegion
    lamb_exportVolumeRegion(_geomRegion->volumes, os);

    //! nodes
    os << "nodes " << _geomRegion->nodes.size() << "\n";
    exportVecDat<VectorDouble>(_geomRegion->nodes, os);

    //! PatchRegion
    lamb_exportPatchRegion(_geomRegion->patches, os);

    //! ZoneRegion
    lamb_exportZoneRegion(_geomRegion->zones, os);

    //! SizeRegion
    lamb_exportSizeRegion(_geomRegion->sizes, os);

    //! solidFaces
    os << "solidFaces " << _geomRegion->solidFaces.size() << "\n";
    exportVecDat<VectorInt>(_geomRegion->solidFaces, os);

    //! solidHoles
    os << "solidHoles " << _geomRegion->solidHoles.size() << "\n";
    exportVecDat<VectorInt>(_geomRegion->solidHoles, os);

    //! voidSolids
    os << "voidSolids " << _geomRegion->voidSolids.size() << "\n";
    exportVecDat<VectorInt>(_geomRegion->voidSolids, os);

    //! CellSetRegion
    lamb_exportCellSets(_geomRegion->cellSets, os);

    //! FaceSetRegion
    lamb_exportFaceSets(_geomRegion->faceSets, os);

    //! MarkerRegion
    lamb_exportFluidMarkers(_geomRegion->fluidMarkers, os);

    //! DomainRegion
    lamb_exportDomainRegion(_geomRegion->domains, os);

    //! radiationBlockFaces
    os << "radiationBlockFaces " << _geomRegion->radiationBlockFaces.size() << "\n";
    exportVecDat<VectorInt>(_geomRegion->radiationBlockFaces, os);

    //! tolerance
    os << "tolerance: " << _geomRegion->tolerance << "\n";
    //! smoothFactor
    os << "smoothFactor: " << _geomRegion->smoothFactor << "\n";
    //! maxAspectRatio
    os << "maxAspectRatio: " << _geomRegion->maxAspectRatio << "\n";
    //! minCellSize
    os << "minCellSize: " << _geomRegion->minCellSize[0] << " "
        << _geomRegion->minCellSize[1] << " " << _geomRegion->minCellSize[2] << "\n";

    os.close();

    return true;
}

bool serializeOctree(OctreeGeometry*& _geomOctree, const std::string& path)
{
    auto lamb_exportTriangleOctree = [&](std::vector<mesh_cm::TriangleOctree>& triangles, ofstream& os)
    {
        size_t sSize = triangles.size();
        os << "triangles " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crTriangleOctree = triangles[sIdx];
            os << "TriangleOctree" << sIdx << "\n";
            os << "nodesIdx: " << crTriangleOctree.nodes[0] << " " << crTriangleOctree.nodes[1] << " " << crTriangleOctree.nodes[2] << "\n";
            os << "normal: " << crTriangleOctree.normal[0] << " " << crTriangleOctree.normal[1] << " " << crTriangleOctree.normal[2] << "\n";
            os << "solidID: " << crTriangleOctree.solidID << " faceID: " << crTriangleOctree.faceID
                << " contact: " << crTriangleOctree.contact << " resistance: " << crTriangleOctree.resistance << "\n";
        }
        os << "\n";
    };

    auto lamb_exportPatchOctree = [&](mesh_cm::PatchOctree& patchOctree, ofstream& os)
    {
        os << "name: " << patchOctree.name << " type: " << patchOctree.type << "\n";

        //! triangleOctree
        lamb_exportTriangleOctree(patchOctree.triangles, os);

        os << "featured: " << patchOctree.featured << " divideLevel: " << patchOctree.divideLevel << "\n";
        os << "\n";
    };

    auto lamb_exportSystems = [&](OctreeGeometry*& _geomOctree, ofstream& os)
    {
        size_t sysLen = sizeof(_geomOctree->systems);
        size_t patchOctreeLen = sizeof(_geomOctree->systems[0]);
        int sysSize = sysLen / patchOctreeLen;

        sysSize = 6;
        for (int sIdx = 0; sIdx < sysSize; ++sIdx)
        {
            auto& crPatchOctree = _geomOctree->systems[sIdx];
            lamb_exportPatchOctree(crPatchOctree, os);
        }
        os << "\n";
    };

    auto lamb_exportPatches = [&](std::vector<mesh_cm::PatchOctree>& patches, ofstream& os)
    {
        os << "\n";
        size_t sSize = patches.size();
        os << "patches " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crPatchOctree = patches[sIdx];
            os << "PatchOctree" << sIdx << ":\n";

            lamb_exportPatchOctree(crPatchOctree, os);
        }
        os << "\n";
    };

    auto lamb_exportVolumes = [&](std::vector<mesh_cm::VolumeOctree>& volumes, ofstream& os)
    {
        size_t sSize = volumes.size();
        os << "\n";
        os << "volumes " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crVolumeOctree = volumes[sIdx];
            os << "VolumeOctree" << sIdx << ":\n";

            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crVolumeOctree.range[rIdx] << " ";
            }
            os << "\n";

            os << "maxMeshSize: " << crVolumeOctree.maxMeshSize[0] << " " << crVolumeOctree.maxMeshSize[1] << " " << crVolumeOctree.maxMeshSize[2] << "\n";
            os << "minMeshSize: " << crVolumeOctree.minMeshSize[0] << " " << crVolumeOctree.minMeshSize[1] << " " << crVolumeOctree.minMeshSize[2] << "\n";
        }
        os << "\n";
    };

    auto lamb_exportZones = [&](std::vector<mesh_cm::ZoneOctree>& zones, ofstream& os)
    {
        size_t sSize = zones.size();
        os << "\n";
        os << "zones " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crZoneOctree = zones[sIdx];
            os << "ZoneOctree" << sIdx << ":\n";
            os << "name: " << crZoneOctree.name << " method: " << crZoneOctree.method << "\n";
            lamb_exportTriangleOctree(crZoneOctree.triangles, os);
            os << "featured: " << crZoneOctree.featured << " divideLevel: " << crZoneOctree.divideLevel << "\n";
        }
        os << "\n";
    };

    auto lamb_exportSizes = [&](std::vector<mesh_cm::SizeOctree>& sizes, ofstream& os)
    {
        size_t sSize = sizes.size();
        os << "\n";
        os << "sizes " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crSizeOctree = sizes[sIdx];
            os << "SizeOctree" << sIdx << ":\n";

            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crSizeOctree.range[rIdx] << " ";
            }
            os << "\n";

            os << "maxMeshSize: " << crSizeOctree.maxMeshSize[0] << " " << crSizeOctree.maxMeshSize[1] << " " << crSizeOctree.maxMeshSize[2] << "\n";
            os << "minMeshSize: " << crSizeOctree.minMeshSize[0] << " " << crSizeOctree.minMeshSize[1] << " " << crSizeOctree.minMeshSize[2] << "\n";
        }
        os << "\n";
    };

    auto lamb_exportcellSets = [&](std::vector<mesh_cm::CellSetOctree>& cellSets, ofstream& os)
    {
        size_t sSize = cellSets.size();
        os << "\n";
        os << "cellSets " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crCellSetOctree = cellSets[sIdx];
            os << "CellSetOctree" << sIdx << ":\n";

            os << "name: " << crCellSetOctree.name << " method: " << crCellSetOctree.method << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crCellSetOctree.range[rIdx] << " ";
            }
            os << "\n";

            os << "direction: " << crCellSetOctree.direction << " solidID: " << crCellSetOctree.solidID
                << " featured: " << crCellSetOctree.featured << "\n";
        }
        os << "\n";
    };

    auto lamb_exportfaceSets = [&](std::vector<mesh_cm::FaceSetOctree>& faceSets, ofstream& os)
    {
        size_t sSize = faceSets.size();
        os << "\n";
        os << "faceSets " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crFaceSetOctree = faceSets[sIdx];
            os << "FaceSetOctree" << sIdx << ":\n";

            os << "name: " << crFaceSetOctree.name << " method: " << crFaceSetOctree.method << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crFaceSetOctree.range[rIdx] << " ";
            }
            os << "\n";

            os << "normal: " << crFaceSetOctree.normal << " featured: " << crFaceSetOctree.featured << "\n";
        }
        os << "\n";
    };

    auto lamb_exportfluidMarkers = [&](std::vector<mesh_cm::MarkerOctree>& fluidMarkers, ofstream& os)
    {
        size_t sSize = fluidMarkers.size();
        os << "\n";
        os << "fluidMarkers " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crMarkerOctree = fluidMarkers[sIdx];
            os << "MarkerOctree" << sIdx << ":\n";

            os << "name: " << crMarkerOctree.name << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crMarkerOctree.range[rIdx] << " ";
            }
            os << "\n";
        }
        os << "\n";
    };

    auto lamb_exportdomains = [&](std::vector<mesh_cm::DomainOctree>& domains, ofstream& os)
    {
        size_t sSize = domains.size();
        os << "\n";
        os << "domains " << sSize << "\n";
        for (size_t sIdx = 0; sIdx < sSize; ++sIdx)
        {
            auto& crDomainOctree = domains[sIdx];
            os << "DomainOctree" << sIdx << ":\n";

            os << "name: " << crDomainOctree.name << " type: " << crDomainOctree.type << "\n";
            os << "range: ";
            for (int rIdx = 0; rIdx < 6; ++rIdx)
            {
                os << crDomainOctree.range[rIdx] << " ";
            }
            os << "\n";
        }
        os << "\n";
    };


    ofstream os;
    os.open(path.c_str(), ios::out | ios::trunc);
    os << fixed;
    os << std::setprecision(20);
    os.setf(ios_base::showpoint);

    //! systems
    lamb_exportSystems(_geomOctree, os);

    //! volumes
    lamb_exportVolumes(_geomOctree->volumes, os);

    //! nodes
    os << "nodes " << _geomOctree->nodes.size() << "\n";
    exportVecDat<VectorDouble>(_geomOctree->nodes, os);

    //! patches
    lamb_exportPatches(_geomOctree->patches, os);

    //! zones
    lamb_exportZones(_geomOctree->zones, os);

    //! sizes
    lamb_exportSizes(_geomOctree->sizes, os);

    //! solidFaces
    os << "solidFaces " << _geomOctree->solidFaces.size() << "\n";
    exportVecDat<VectorInt>(_geomOctree->solidFaces, os);

    //! voidSolids
    os << "voidSolids " << _geomOctree->voidSolids.size() << "\n";
    exportVecDat<VectorInt>(_geomOctree->voidSolids, os);

    //! solidResistance
    os << "solidResistance " << _geomOctree->solidResistance.size() << "\n";
    exportVecDat<VectorDouble>(_geomOctree->solidResistance, os);

    //! cellSets
    lamb_exportcellSets(_geomOctree->cellSets, os);

    //! faceSets
    lamb_exportfaceSets(_geomOctree->faceSets, os);

    //! fluidMarkers
    lamb_exportfluidMarkers(_geomOctree->fluidMarkers, os);

    //! domains
    lamb_exportdomains(_geomOctree->domains, os);

    //! tolerance
    os << "tolerance: " << _geomOctree->tolerance[0] << " " << _geomOctree->tolerance[1] << " " << _geomOctree->tolerance[2] << "\n";
    //! tolAreaRatio
    os << "tolAreaRatio: " << _geomOctree->tolAreaRatio[0] << " " << _geomOctree->tolAreaRatio[1] << " " << _geomOctree->tolAreaRatio[2] << "\n";
    //! smoothFactor
    os << "smoothFactor: " << _geomOctree->smoothFactor << "\n";
    //! divideLevel
    os << "divideLevel: " << _geomOctree->divideLevel << "\n";
    //! activePlaneFeature
    os << "activePlaneFeature: " << _geomOctree->activePlaneFeature << "\n";

    return true;
}