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


(be aware memleak with nonpaged will start to fail when windows decides that the process cannot keep the memory into RAM, and memleak will fail alltogethor when the windows hits it with OOM)