LONGEST COMMON SUBSEQUNCE
// L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1]
int L[m+1][n+1];
for (int i=0; i<=m; i++)
    for (int j=0; j<=n; j++)
        if (i == 0 || j == 0)
            L[i][j] = 0;
        else if (X[i-1] == Y[j-1])
            L[i][j] = L[i-1][j-1] + 1;
        else
            L[i][j] = max(L[i-1][j], L[i][j-1]);
return L[m][n];

LONGEST COMMON SUBSTRING
// LCSuff[i][j] contains length of longest common suffix of X[0..i-1] and Y[0..j-1]
int LCSuff[m+1][n+1];
int result = 0;  // To store length of the longest common substring
for (int i=0; i<=m; i++)
    for (int j=0; j<=n; j++)
        if (i == 0 || j == 0)
            LCSuff[i][j] = 0;
        else if (X[i-1] == Y[j-1]) {
            LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
            result = max(result, LCSuff[i][j]);
        } else
            LCSuff[i][j] = 0;
return result;

KNAPSACK
// K[i,j] is max value with items 0..i and capacity j
int K[n+1][W+1];
for (int i = 0; i <= n; i++)
    for (int w = 0; w <= W; w++)
        if (i==0 || w==0)
            K[i][w] = 0;
        else if (items[i-1].second <= w)
            K[i][w] = max(items[i-1].first + K[i-1][w-items[i-1].second],  K[i-1][w]);
        else
            K[i][w] = K[i-1][w];
return K[n][W];
