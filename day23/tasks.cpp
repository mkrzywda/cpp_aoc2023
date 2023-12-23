#include "tasks.h"
#include <algorithm>

int findMaxSteps(int x, int y, const GridInfo& gridInfo, std::vector<std::vector<bool>>& vis) {
    if (x < 0 || x > gridInfo.n - 1 || y < 0 || y > gridInfo.m - 1 || gridInfo.grid[x][y] == '#' || vis[x][y]) 
        return INF;
    
    if (x == gridInfo.n - 1 && y == gridInfo.m - 2) 
        return 0;

    vis[x][y] = true;
    int ans = INF;
    
    if (gridInfo.grid[x][y] == '>' || gridInfo.grid[x][y] == '.') 
        ans = std::max(ans, findMaxSteps(x, y + 1, gridInfo, vis));
    
    if (gridInfo.grid[x][y] == '<' || gridInfo.grid[x][y] == '.') 
        ans = std::max(ans, findMaxSteps(x, y - 1, gridInfo, vis));
    
    if (gridInfo.grid[x][y] == 'v' || gridInfo.grid[x][y] == '.') 
        ans = std::max(ans, findMaxSteps(x + 1, y, gridInfo, vis));
    
    if (gridInfo.grid[x][y] == '^' || gridInfo.grid[x][y] == '.') 
        ans = std::max(ans, findMaxSteps(x - 1, y, gridInfo, vis));

    vis[x][y] = false;
    return ans + 1;
}

int findMaxStepsNoDirection(int x, int y, const GridInfo& gridInfo, std::vector<std::vector<bool>>& vis) {
    if (x < 0 || x > gridInfo.n - 1 || y < 0 || y > gridInfo.m - 1 || gridInfo.grid[x][y] == '#' || vis[x][y]) 
        return INF;

    if (x == gridInfo.n - 1 && y == gridInfo.m - 2) 
        return 0;

    vis[x][y] = true;
    int ans = INF;
    
    ans = std::max(ans, findMaxStepsNoDirection(x, y + 1, gridInfo, vis));
    ans = std::max(ans, findMaxStepsNoDirection(x, y - 1, gridInfo, vis));
    ans = std::max(ans, findMaxStepsNoDirection(x + 1, y, gridInfo, vis));
    ans = std::max(ans, findMaxStepsNoDirection(x - 1, y, gridInfo, vis));

    vis[x][y] = false;
    return ans + 1;
}
