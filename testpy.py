n = int(input())
s = [int(i) for i in input().split()]
ans=0
for i in s:
    ans += i**2*2**(n-1)
    ans%=1000000007
dp = [[0,0,0] for i in range(n+1)]
dp[0][0]=1
for i in range(n+1):
    for j in range(3):
        if i>=1:dp[i][j]+=dp[i-1][j]
        dp[i][j]%=1000000007
        if i>=1 and j>=1:dp[i][j]+=s[i-1]*dp[i-1][j-1]
        dp[i][j]%=1000000007
ans+=dp[n][2]*2**(n-1)
ans%=1000000007
print(ans)