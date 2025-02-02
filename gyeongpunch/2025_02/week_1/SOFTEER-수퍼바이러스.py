k, p, n = map(int, input().split())
mod = 1000000007
result = (k * pow(p, n*10, mod))%mod
print(result)