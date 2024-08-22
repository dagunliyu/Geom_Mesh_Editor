
#include <unordered_map>
#include <unordered_set>
struct entity
{
    double x, y, z;
};

class TVector3d
{
    double x, y, z;
}

class LC_Elem;

void write_Triangles(const std::unordered_set<entity> &faceElems, std::string file)
{
    std::unordered_map<entity, size_t> nodeIdMap;
    // merge a tri
    size_t triangleNum = faceElems.size();
    std::vector<TVector3d> allPoints;
    std::vector<std::pair<entity, std::array<int, 3>>> allTriangles;
    std::vector<entity> nodeEntityIdx;
    allPoints.reserve(triangleNum);
    nodeEntityIdx.reserve(triangleNum);
    allTriangles.reserve(triangleNum);

    size_t countId(0);
    for (auto elem : faceElems)
    {
        auto tri = LC_Elem::FromEntity(elem);
        std::array<int, 3> triId;
        for (int i = 0; i < 3; i++)
        {
            entity node = tri->GetNode(i);
            auto nodeIdMapIt = nodeIdMap.find(node);
            if (nodeIdMapIt == nodeIdMap.end())
            {
                allPoints.push_back(LC_Node::FromEntity(node)->d_vPos);
                nodeEntityIdx.push_back(node);
                triId[i] = countId;

                nodeIdMap.insert(std::pair<entity, int>{node, countId});
                ++countId;
            }
            else
            {
                triId[i] = nodeIdMapIt->second;
            }
        }
        allTriangles.emplace_back(std::pair<entity, std::array<int, 3>>{elem, std::move(triId)});
    }
    allPoints.shrink_to_fit();
    nodeEntityIdx.shrink_to_fit();    

    // TODO:
}