#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <tuple>
#include <chrono>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine gen(seed);
std::uniform_real_distribution<double> distribution(-50.0, 50.0);

class vertex
{
    public:
        float x;
        float y;
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
        vertex from;
        vertex to;
        float dist;
    public:
        edge(vertex& f, vertex& t) : from(f), to(t)
        {
            dist = std::sqrt(std::pow(to.x-from.x, 2)+std::pow(to.y-from.y, 2));
        }
        void getedge()
        {
            from.getvertex();
            std::cout << '-' << dist << "->";
            to.getvertex();
        }

};

class graph
{
    public:
        float length;
        float width;
        std::vector<vertex> vertices;
        std::vector<edge> edges;
        graph(float l = 100, float w = 100)
        {
            length = l;
            width = w;
        }
        void addvertex(const vertex& v1)
        {
            vertices.push_back(v1);
        }
        void addedges(const edge& e1)
        {
            edges.push_back(e1);
        }
        void showgraph()
        {
            std::cout << "Vertices: " << '[';
            for (int i = 0; i < vertices.size(); ++i)
            {
                vertices[i].getvertex();
                if (i != vertices.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << ']' << std::endl;

            std::cout << "Edges: " << '[';
            for (int i = 0; i < edges.size(); ++i)
            {
                edges[i].getedge();
                if (i != edges.size() - 1)
                {
                    std::cout << ", " << std::endl;
                }
            }
            std::cout << "]\n";
        }
};

std::tuple<vertex, float> closest(vertex& new_vert, graph& g)
{
    float d = 100000000;
    vertex final;
    for (auto v : g.vertices)
    {
        if (std::sqrt(std::pow(new_vert.x - v.x, 2) + std::pow(new_vert.y - v.y, 2)) < d)
        {
            d = std::sqrt(std::pow(new_vert.x - v.x, 2) + std::pow(new_vert.y - v.y, 2));
            final = v;
        }
    }
    std::tuple<vertex, float> tup;
    tup = std::make_tuple(final, d);
    return tup;
}

void rrt(vertex& start, vertex& goal, int num_of_nodes, graph& g)
{
    bool done = false;
    for (int i = 0; i < num_of_nodes; ++i)
    {
        vertex new_vert(distribution(gen), distribution(gen));
        std::tuple<vertex, float> tup = closest(new_vert, g);
        vertex v = std::get<0>(tup);
        float d = std::get<1>(tup);
            
        if (d > 2)
        {
            float slope = (new_vert.y - v.y) / (new_vert.x - v.x);
            new_vert.x = std::sqrt(4.0/(std::pow(slope,2)+1.0)) + v.x;
            new_vert.y = slope * (new_vert.x-v.x) + v.y;
        }
        if (std::sqrt(std::pow(new_vert.x - goal.x, 2) + std::pow(new_vert.y - goal.y, 2)) <= 3)
        {
            done = true;
        }
        g.addvertex(new_vert);
        edge e0(v, new_vert);
        g.addedges(e0);
        if (done)
        {
            break;
        }
    }
}

int main()
{
    graph g;
    vertex start(0, 0);
    vertex goal(10, 10);
    g.addvertex(start);
    int num_of_nodes = 500;
    rrt(start, goal, num_of_nodes, g);
    //g.showgraph();
    std::cout << g.vertices.size() << std::endl;
    std::cout << g.edges.size() << std::endl;

    return 0;
}
