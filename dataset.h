
#ifndef DATASET
#define DATASET


#include "./alter/tools.h"

const int N = 500, M = N * N * 2;
typedef int weight_type;

struct Loader
{
    struct edge
    {
        int nx, to;
        weight_type w;
    }e[M];

    int head[N], mal=1, n, m;

    void addedge(int u, int v, weight_type w)
    {
        e[mal].to = v; e[mal].w = w; e[mal].nx = head[u]; head[u] = mal++;
    }

    void clear()
    {
        memset(head, 0 ,sizeof(head));
        mal = 1;
    }
};

/*
 * Integer数据集
 * 
 * @method: dump_info(), load_info(), batch_ints(), load_testcase_ints()
 * @attribute: possible_space_size()
 * 
 * 仅仅适合本次排序实验的子类
 */
class DirectedGraphSet: public DataSet
{
protected:

public:

    DirectedGraphSet(const std::string &fold_path, const std::string &dataset_name, const std::string suffix=".txt") :
        DataSet(fold_path, dataset_name, suffix)
    {
    }

    void load_testcase(Loader &ldr, int idx)
    {
        self_handle.open(self_file_prefix + std::to_string(idx) + self_file_suffix, std::ios::in);
        if (!self_handle.opening()) {
            throw std::domain_error(self_file_prefix + std::to_string(idx) + ".txt is not opening");
        }
        ldr.clear();
        self_handle.get(ldr.n);
        self_handle.get(ldr.m);
        //std:: cout  << ldr.n << " " << ldr.m;
        for (int i = 1; i <= ldr.m; i++) {
            int u, v;
            weight_type w;
            self_handle.get(u);
            self_handle.get(v);
            self_handle.get(w);
            ldr.addedge(u, v, w);
            //std::cout << u << " " << v << " " << w << "\n";
        }
        self_handle.close();
    }

};


#endif

