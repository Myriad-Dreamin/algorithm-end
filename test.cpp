#include <iostream>
#include <cstring>
#include <queue>
#include "dataset.h"
#include "alter/tester.h"

weight_type spfa(const Loader &ldr, int s, int t)
{
    static weight_type d[N];
    static bool vis[N];
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    std::queue<int> Q;

    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(Q.size()) {
        auto u = Q.front();
        Q.pop();
        vis[u] = 0;
        for (int i = ldr.head[u]; i; i = ldr.e[i].nx) {
            auto v = ldr.e[i].to;
            if (d[v] > d[u] + ldr.e[i].w) {
                d[v] = d[u] + ldr.e[i].w;
                if (!vis[v]) {
                    Q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return d[t];
}


weight_type floyd(const Loader &ldr, int s, int t)
{
    static weight_type d[N][N];
    for (int i = 1; i <= ldr.n; i++) {
        for (int j = 1; j <= ldr.n; j++) {
            d[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= ldr.n; i++) {
        for (int j = ldr.head[i]; j; j = ldr.e[j].nx) {
            d[i][ldr.e[j].to] = std::min(d[i][ldr.e[j].to], ldr.e[j].w);
        }
    }
    for (int k = 1; k <= ldr.n; k ++) {
        for (int i = 1; i <= ldr.n; i ++) {
            for (int j = 1; j <= ldr.n; j ++) {
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    return d[s][t];
}
Loader *ldr = new Loader;


int main() {
    DirectedGraphSet Grapher("./test", "test", ".in");
    Grapher.load_info();
    Tester ret("./random.csv");


    for (int i = 1; i <= Grapher.size(); i++) {
        Grapher.load_testcase(*ldr, i);

        ret.block(ldr->n);
        weight_type std_ret, m_ret;
        ret.run([&]() mutable {
            std_ret = floyd(*ldr, 1, ldr->n);
        });
        ret.show();
        ret.block(ret.used_time());
        ret.settle_clock();

        ret.run([&]() mutable {
            m_ret = spfa(*ldr, 1, ldr->n);
        }, [&]() {
            assert(m_ret == std_ret);
        });
        ret.show();
        ret.block(ret.used_time());
        ret.settle_clock();

        ret.newline();
        
    }
}

/*
4 6
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
 */