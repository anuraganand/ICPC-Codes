
int gcd(int a, int b) {
    return __gcd(a, b);
}

int lcm(int a, int b) {
    int hcf = gcd(a, b);
    if(hcf == 0)
        return 0;
    return (a * b) / hcf;
}

const int P = 2;

int rank(int n, int m) {
    int row = 0;
    for(int col = 0; col < m; col++) {
        int maxValRow = row;
        for(int r = row + 1; r < n; r++) {
            if(v[r][col] > v[maxValRow][col])
                maxValRow = r;
        }

        if(v[maxValRow][col] == 0)
            continue;

        if(maxValRow != row) 
            swap(v[row], v[maxValRow]);

        for(int r = row + 1; r < n; r++) {
            if(v[r][col] == 0)
                continue;
            int lmul = lcm(v[row][col], v[r][col]);
            int mul1, mul2;

            if(v[row][col] != 0)
                mul1 = lmul / v[row][col];
            else
                mul1 = 0;

            if(v[r][col] != 0)
                mul2 = lmul / v[r][col];
            else
                mul2 = 0;

            for(int c = 0; c < m; c++) {
                v[r][c] = (mul1 * v[row][c] - mul2 * v[r][c] + 2) % P;
            }
        }
        row++;
        if(row == n)
            break;
    }

    int rnk = n;
    for(int r = n - 1; r >= 0; r--) {
        bool allZeros = true;
        for(int c = 0; c < m; c++) {
            if(v[r][c] != 0) {
                allZeros = false;
                break;
            }
        }
        if(allZeros) rnk--;
        else break;
    }

    return rnk;
}