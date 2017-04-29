// @author cebrusfs
// headers {{{
#include<bits/stdc++.h>
using namespace std;
// }}}
// macros {{{
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define UNIQUE(x) (sort(ALL(x)), ((x).erase(unique(ALL(x)), (x).end())))
#define MSA(x, v) std::fill(ALL(x), (v))
#define MS(st, ed, v) std::fill((st), (ed), (v))

#define REP(i,n) for(int i=0;i<(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=(b);i++)

#define PER(i,n) for(int i=(n)-1;i>=0;i--)
#define PER1(i,a,b) for(int i=(a);i>=(b);i--)

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

typedef pair<int, int> PII;
#define MP make_pair
#define F first
#define S second

typedef vector<int> VI;
#define PB push_back
#define PF push_front

#define PPB pop_back
#define PPF pop_front

#define runtime() ((double)clock() / CLOCKS_PER_SEC)

const double eps = 1e-7;

// C++11
#if __cplusplus >= 201103L
#define MT make_tuple
typedef tuple<int, int> TII;

// dump() {{{
template<typename T>
void _dump(const char* s, T&& head) {
    cerr<< s << "=" << head << endl;
}

template<typename T, typename... Args>
void _dump(const char* s, T&& head, Args&&... tail) {
    int c = 0;
    while (*s!=',' || c!=0) {
        if (*s=='(' || *s=='[' || *s=='{') c++;
        if (*s==')' || *s==']' || *s=='}') c--;
        cerr << *s++;
    }
    cerr << "=" << head << ", ";
    _dump(s+1, tail...);
}

#ifdef FISH
#define dump(...) do { \
    fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
    _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0);
#else
#define dump(...) ;
#endif

template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[";
    for (auto it = b; it != e; it++) s << (it == b ? "":" ") << *it;
    s << "]";
    return s;
}

template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<(ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<(ostream &s, const unordered_set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<(ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<(ostream &s, const unordered_map<A,B> &c) { return _out(s,ALL(c)); }
// }}}

#endif
// }}}

#define MAX 10
#define COLOR_MAX 5
#define RANDOM_TIME 5
#define MOD1 1000000000000000003LL
#define MOD2 1000000000000000009LL


// Bonus = 2000 - Blocks^2 * 20
// score = block^2 * 5


const int EMPTY = 0;

const int DIRATION[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

//const char charset[] = ".rgbyp";
const int ASCII_COLOR[] = {40, 41, 42, 44, 43, 45};

/*
typedef vector<PII> GROUP;
#define PACK(x, y) (MP(x, y))
#define FST(x) ((x).first)
#define SND(x) ((x).second)
*/
typedef vector<int> GROUP;
#define PACK(x, y) ((x) * 128 + (y))
#define FST(x) ((x) / 128)
#define SND(x) ((x) % 128)

typedef pair<long long, long long> HASH;

bool cmp(const GROUP& a, const GROUP& b)
{
    return a.size() < b.size();
}

inline bool move_down(char col[])
{
    int real_r = MAX - 1;

    for (int r = MAX - 1; r >= 0; --r)
        if (col[r] != EMPTY)
            col[real_r--] = col[r];
    for (int r = real_r; r >= 0; --r)
        col[r] = EMPTY;

    // return true if empty column
    return real_r == MAX - 1;
}



class Game {
  public:
    int step;
    char raw[MAX*MAX][MAX][MAX];

    // MAX*MAX x MAX pointer
    char *history[MAX*MAX][MAX];

    char **mp;

    map<HASH, int> hash_table;

    Game () {
        step = 0;
        mp = NULL;
    }

    void generate()
    {
        step = 0;

        for (int r = 0; r < MAX; ++r)
            for (int c = 0; c < MAX; ++c)
                raw[0][c][r] = 1 + rand() % COLOR_MAX;

        for (int c = 0; c < MAX; ++c)
            history[0][c] = raw[0][c];

        mp = history[0];
    }

    int eliminate(const GROUP& group)
    {
        bool used[MAX];
        memset(used, false, sizeof(used));

        for (const auto& p : group)
            used[FST(p)] = true;

        // copy ptr
        static_assert(sizeof(history[step]) == sizeof(char*) * MAX);
        memcpy(history[step+1], history[step], sizeof(history[step]));

        // copy on write
        for (int c = 0; c < MAX; ++c)
            if (used[c])
            {
                static_assert(sizeof(raw[step + 1][c]) == sizeof(char) * MAX);

                // find a new place
                history[step + 1][c] = raw[step + 1][c];
                // copy
                memcpy(history[step + 1][c], history[step][c], sizeof(raw[step + 1][c]));
            }

        // copied, and step forward!
        step += 1;
        mp = history[step];

        // eliminate on new copy
        for (const auto& p : group)
            mp[FST(p)][SND(p)] = EMPTY;

        bool is_empty[MAX];
        memset(is_empty, false, sizeof(is_empty));
        for (int c = 0; c < MAX; ++c)
            is_empty[c] = move_down(mp[c]);

        // move down & move left
        int real_c = 0;
        char* empty_col = NULL;
        for (int c = 0; c < MAX; ++c)
        {
            if (used[c] and is_empty[c])
                empty_col = mp[c];
            else
                mp[real_c++] = mp[c];
        }
        assert((real_c < MAX and empty_col != NULL) or real_c == MAX);
        for (int c = real_c; c < MAX; ++c)
            mp[c] = empty_col;

        return group.size() * group.size() * 5;
    }

    void recover(int to_step)
    {
        step = to_step;
        mp = history[step];
    }

    void pretty_print() const
    {
        for (int r = 0; r < MAX; ++r)
        {
            for (int c = 0; c < MAX; ++c)
            {
                int hight = 1;
                int color = ASCII_COLOR[(int) mp[c][r]];

                printf("\x1b[%d;%dm  \x1b[m", hight, color);
            }
            printf("\n");
        }
        printf("\n");
    }

    int cal_end() const
    {
        int cnt = 0;
        for (int i = 0; i < MAX; ++i)
            for (int j = 0; j < MAX; ++j)
                if (mp[i][j] != EMPTY)
                    cnt ++;
        return max(2000 - cnt * cnt * 20, 0);
    }

    int h_func()
    {
        int currect_step = step;

        int best = -1;

        // random walk
        for (int i = 0; i < RANDOM_TIME; ++i)
        {
            int score = 0;

            while (true)
            {
                const auto& gs = get_groups();
                if (gs.empty()) break;

                const auto& p = gs[rand() % gs.size()];
                score += eliminate(p);
            }
            score += cal_end();

            best = max(best, score);

            recover(currect_step);
        }

        // greedy choose smallest
        do {
            int score = 0;

            while (true)
            {
                const auto gs = get_groups();
                if (gs.empty()) break;

                const auto& p = *min_element(gs.begin(), gs.end(), cmp);
                score += eliminate(p);
            }
            score += cal_end();

            best = max(best, score);

            recover(currect_step);

        } while (false);

        /*
        //bad
        {
            int cnt[6];
            memset(cnt, 0, sizeof(cnt));
            for (const auto& g: get_groups(true))
            {
                const auto& p = g.front();
                cnt[(int)mp[p.first][p.second]] += g.size();
            }
            int ans = 0;
            for (int i = 1; i < 6; ++i)
                ans += cnt[i] * cnt[i] * 5;

            ans += 2000;

            dump(ans, best);
        }*/

        return best;
    }

    int solve(int dep, int limit, GROUP *op = NULL)
    {
        if (dep == 0) hash_table.clear();

        // check hash for duplicate puzzle
        auto h = cal_hash();

        auto it = hash_table.find(h);
        if (it != hash_table.end())
            return it->second;

        /*
        dump(step, dep);
        pretty_print();
        */

        int best = -1;

        int currect_step = step;
        if (dep >= limit)
        {
            best = h_func();
            recover(currect_step);
        }
        else
        {
            const auto& gs = get_groups();
            for (const auto& g: gs)
            {
                assert(g.size() >= 2);

                int sc1 = 0, sc2 = 0;
                sc1 += eliminate(g);
                sc2 += solve(dep + 1, limit);

                recover(currect_step);

                int sc = sc1 + sc2;
                if (sc > best)
                {
                    best = sc;

                    if (op != NULL)
                        *op = g;
                }
            }

            if (best == -1)
                best = cal_end();
        }

        hash_table[h] = best;

        return best;
    }

    int parallel_solve(int limit, GROUP *op = NULL)
    {
        const auto& gs = get_groups();

        int best = -1;
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < (int)gs.size(); ++i)
        {
            const auto& g = gs[i];
            assert(g.size() >= 2);

            Game temp_game = *this;
            temp_game.hash_table.clear();


            int sc = 0;
            sc += temp_game.eliminate(g);
            sc += temp_game.solve(1, limit);

            #pragma omp critical
            {
                if (sc > best)
                {
                    best = sc;

                    if (op != NULL)
                        *op = g;
                }
            }
        }

        if (best == -1)
            best = cal_end();

        return best;
    }

  private:
    // bfs
    /*
    long long vis_flag = 0;
    long long vis[MAX][MAX];
    */

    GROUP bfs(int x, int y, bool vis[MAX][MAX], int vis_flag) const
    {
        GROUP q;
        q.reserve(32);

        int fd = 0;
        q.emplace_back(PACK(x, y));
        vis[x][y] = vis_flag;

        while (fd < (int)q.size())
        {
            const auto& p = q[fd++];

            for (int d = 0; d < 4; ++d)
            {
                int a = FST(p) + DIRATION[d][0];
                int b = SND(p) + DIRATION[d][1];

                if (0 <= a and a < MAX and 0 <= b and b < MAX
                    and vis[a][b] != vis_flag and mp[x][y] == mp[a][b])
                {
                    vis[a][b] = vis_flag;
                    q.emplace_back(PACK(a, b));
                }
            }
        }
        return q;
    }

    vector<GROUP> get_groups(bool all=false) const
    {
        vector<GROUP> ret;
        ret.reserve(128);

        bool vis[MAX][MAX];
        memset(vis, 0, sizeof(vis));
        int vis_flag = 1;

        for (int c = MAX - 1; c >= 0; --c)
            for (int r = 0; r < MAX; ++r)
                if(mp[c][r] != EMPTY and vis[c][r] != vis_flag)
                {
                    const auto& group = bfs(c, r, vis, vis_flag);
                    if (all or group.size() >= 2)
                        ret.emplace_back(move(group));
                }
        return ret;
    }

    HASH cal_hash() const
    {
        long long h1 = 0, h2 = 0;

        // 0 ~ 5
        for (int c = 0; c < MAX; ++c)
            for (int r = 0; r < MAX; ++r)
                h1 = (h1 * 6 + mp[c][r]) % MOD1;
        for (int c = 0; c < MAX; ++c)
            for (int r = 0; r < MAX; ++r)
                h2 = (h2 * 6 + mp[c][r]) % MOD2;
        return MP(h1, h2);
    }

};


int main()
{
    Game game;

    srand(514514);
    game.generate();

    int score = 0;
    while (true)
    {
        struct timespec start, finish;

        clock_gettime(CLOCK_MONOTONIC, &start);

        printf("Step %d: %d\n", game.step, score);
        game.pretty_print();

        GROUP action;

        //int predict = game.solve(0, 5 + max(game.step - 10, 0), &action);
        int predict = game.parallel_solve(5 + max(game.step - 8, 0), &action);

        clock_gettime(CLOCK_MONOTONIC, &finish);

        double elapsed = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        dump(elapsed, action, predict, score + predict);

        if (action.size() == 0)
        {
            // game is end
            score += game.cal_end();
            break;
        }
        score += game.eliminate(action);
    }
    printf("End Step %d: %d\n", game.step, score);
}

