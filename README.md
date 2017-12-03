# Advent of Code 2017

> Solutions for the [Advent of Code 2017](http://adventofcode.com/2017) written
> in native Reason

Each day has a solution file (`<day>.re`) and a test file (`<day>_test.re`). To
run all the tests run

```
$ jbuilder runtest
```

And for a specific day use

```
$ jbuilder runtest <day>
```

To set up a watcher while writing code use
[Watchman](https://facebook.github.io/watchman)

```
$ watchman-make -p "*.re" --run "jbuilder runtest"
```
