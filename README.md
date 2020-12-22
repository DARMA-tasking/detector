# *detector* => DARMA/detector

![Build Status](https://travis-ci.com/DARMA-tasking/detector.svg?branch=master)
![](https://github.com/DARMA-tasking/detector/workflows/Docker%20Image%20CI/badge.svg)

## Introduction : What is *detector*

*detector* is a small library that implements static/compile-time type
introspection in C++. With this code, we can check if a type has methods, type
aliases, or members that are exactly matching or convertible to a particular
interface. Because this library requires C++-14, it is separated from the other
DARMA/* libraries.
