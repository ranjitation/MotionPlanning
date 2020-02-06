#include <iostream>
#include <vector>
#include <queue>

class vertex
{
    protected:
        float x;
        float y;
    public:
        vertex(float _x = 0, float _y = 0)
        {
            x = _x;
            y = _y;
        }
        void getvertex()
        {
            std::cout << '[' << x << ", " << y << ']';
        }
};

class edge
{
    protected:
        vertex* from;
        vertex* to;
        float dist;
    public:
        edge(vertex &f, vertex &t,const float d)
        {
            from = &f;
            to = &t;
            dist = d;
        }
        void getedge()
        {
            from->getvertex();
            std::cout << '-' << dist << "->";
            to->getvertex();
        }

};

class graph
{
    protected:
        float length;
        float width;
        std::vector<vertex> vertices;
        std::vector<edge> edges;
    public:
        graph(float l = 100, float w = 100)
        {
            length = l;
            width = w;
        }
        void addvertex(const vertex &v1)
        {
            vertices.push_back(v1);
        }
        void addedges(const edge &e1)
        {
            edges.push_back(e1);
        }
        void showgraph()
        {
            std::cout << "Vertices: " << '[';
            for (int i=0; i<vertices.size(); ++i)
            {
                vertices[i].getvertex();
                if (i != vertices.size()-1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << ']' << std::endl;

            std::cout << "Edges: " << '[';
            for (int i=0; i<edges.size(); ++i)
            {
                edges[i].getedge();
                if (i != edges.size()-1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "]\n";
        }

};

int main()
{
    vertex v0(1,2);
    vertex v1(2,3);
    edge e0(v0, v1, 5.4);
    e0.getedge();
    graph g;
    g.addvertex(v0);
    g.addvertex(v1);
    g.addedges(e0);
    g.showgraph();
    // for (auto x : {1,2,3,4,5})
    // {
    //     std::cout << x << ',';
    // }
    // std::cout << std::endl;

    return 0;
}