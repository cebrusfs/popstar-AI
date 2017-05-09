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

const char SYMBOL_SET[] = ".rgbyp";
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

GROUP global_best_actions[MAX*MAX];
int global_best_score = 0;

class Game {
  public:
    int step;
    char raw[MAX*MAX][MAX][MAX];

    // MAX*MAX x MAX pointer
    char *history[MAX*MAX][MAX];

    char **mp;

    map<HASH, int> hash_table;

    GROUP actions[MAX*MAX];
    int history_score[MAX*MAX];

    Game () {
        step = 0;
        mp = NULL;
        history_score[0] = 0;
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

    void input()
    {
        printf("[*] Get map from stdin\n");
        for (int r = 0; r < MAX; ++r)
            for (int c = 0; c < MAX; ++c)
            {
                char ch;
                scanf(" %c", &ch);
                auto ptr = strchr(SYMBOL_SET, ch);

                if (ptr == NULL)
                {
                    printf("char: %c (%d)\n", ch, ch);
                    assert(false);
                }
                raw[0][c][r] = ptr - SYMBOL_SET;
            }


        step = 0;
        for (int c = 0; c < MAX; ++c)
            history[0][c] = raw[0][c];

        mp = history[0];
    }
    void file_input(char buf[])
    {
        printf("[*] Get map from file: %s\n", buf);

        FILE* f = fopen(buf, "r");
        assert(f != NULL);
        for (int r = 0; r < MAX; ++r)
            for (int c = 0; c < MAX; ++c)
            {
                char ch;
                fscanf(f, " %c", &ch);
                auto ptr = strchr(SYMBOL_SET, ch);

                if (ptr == NULL)
                {
                    printf("char: %c (%d)\n", ch, ch);
                    assert(false);
                }
                raw[0][c][r] = ptr - SYMBOL_SET;
            }
        fclose(f);


        step = 0;
        for (int c = 0; c < MAX; ++c)
            history[0][c] = raw[0][c];

        mp = history[0];
    }

    int currect_score() const
    {
        return history_score[step];
    }

    int eliminate(const GROUP& group)
    {
        bool used[MAX];
        memset(used, false, sizeof(used));

        int add = group.size() * group.size() * 5;

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
        actions[step] = group;
        history_score[step + 1] = currect_score() + add;
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

        return add;
    }

    void recover(int to_step)
    {
        step = to_step;
        mp = history[step];
    }

    void pretty_print(const GROUP &g = GROUP()) const
    {
        for (int r = 0; r < MAX; ++r)
        {
            for (int c = 0; c < MAX; ++c)
            {
                bool choosed = false;
                for (const auto& idx : g)
                    if (FST(idx) == c and SND(idx) == r)
                        choosed = true;

                int color = ASCII_COLOR[(int) mp[c][r]];

                printf("\x1b[1;%dm%s\x1b[m", color, choosed ? ".." : "  ");
            }
            printf("\n");
        }
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
            while (true)
            {
                const auto gs = get_groups();
                if (gs.empty()) break;

                const auto& p = *min_element(gs.begin(), gs.end(), cmp);
                eliminate(p);
            }
            int score = currect_score() + cal_end();

            best = max(best, score);

            if (score > global_best_score)
            {
                #pragma omp critical
                {
                    global_best_score = score;
                    for (int i = 0; i < step; ++i)
                        global_best_actions[i] = actions[i];
                    global_best_actions[step].clear();
                }
            }

            recover(currect_step);
        }

        // greedy choose smallest
        do
        {
            while (true)
            {
                const auto gs = get_groups();
                if (gs.empty()) break;

                const auto& p = *min_element(gs.begin(), gs.end(), cmp);
                eliminate(p);
            }
            int score = currect_score() + cal_end();
            best = max(best, score);

            if (score > global_best_score)
            {
                #pragma omp critical
                {
                    global_best_score = score;
                    for (int i = 0; i < step; ++i)
                        global_best_actions[i] = actions[i];
                    global_best_actions[step].clear();
                }
            }

            recover(currect_step);

        } while (false);

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

                eliminate(g);
                int sc = solve(dep + 1, limit);

                recover(currect_step);

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

            temp_game.eliminate(g);
            int sc = temp_game.solve(1, limit);

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


int main(int argc, char *argv[])
{
    Game game;
    srand(time(NULL));

    if (argc == 2)
    {
        if (strcmp(argv[1], "-") == 0)
        {
            srand(514514);
            game.generate();
        }
        else
        {
            game.file_input(argv[1]);
        }
    }
    else
    {
        game.input();
    }

    int depth = 5;
    if (getenv("depth") != NULL)
    {
        depth = atoi(getenv("depth"));
    }


    printf("Search depth: %d\n", depth);

    game.pretty_print();

    while (true)
    {
        struct timespec start, finish;

        clock_gettime(CLOCK_MONOTONIC, &start);

        game.parallel_solve(depth + max(game.step - 7, 0));

        clock_gettime(CLOCK_MONOTONIC, &finish);

        double elapsed = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        GROUP action = global_best_actions[game.step];
        dump(elapsed, global_best_score, action);

        if (action.size() == 0)
        {
            // game is end
            break;
        }

        printf("Step %d: \n", game.step);
        game.pretty_print(action);
        game.eliminate(action);
        printf("score --> %d\n\n", game.currect_score());
    }

    int score = game.currect_score() + game.cal_end();
    printf("End Step %d: %d\n", game.step, score);
}

