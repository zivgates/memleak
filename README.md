# MemLeak, a CLI tool to purposly leak memory


It leaks kilobyte amount you pass into the executable


to leak 10KB/ms paged memory (stored in the pagefile when RAM is filled), run this

```
memleak 10 paged
```



to leak 10KB/ms of non-paged memory (forced to the RAM till it fails), run this

```
memleak 10 nonpaged
```