#!/usr/bin/wish -f
#
# Copyright (c) 2012 Karl N. Redgate
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#

graph testGraph

set v1 [testGraph vertex]
Advice t1
t1 enter "puts \"enter v1\""
t1 visit "puts \"visit v1\""
t1 leave "puts \"leave v1\""
$v1 advice [t1]

set v2 [testGraph vertex]
Advice t2
t2 enter "puts \"enter v2\""
t2 visit "puts \"visit v2\""
t2 leave "puts \"leave v2\""
$v2 advice [t2]

set v3 [testGraph vertex]
Advice t3
t3 enter "puts \"enter v3\""
t3 visit "puts \"visit v3\""
t3 leave "puts \"leave v3\""
$v3 advice [t3]

set v4 [testGraph vertex]
Advice t4
t4 enter "puts \"enter v4\""
t4 visit "puts \"visit v4\""
t4 leave "puts \"leave v4\""
$v4 advice [t4]

$v1 connect [$v2 reference]
$v2 connect [$v4 reference]
$v1 connect [$v3 reference]
$v4 connect [$v1 reference]

puts "Depth first search"
testGraph DFS
puts "Breadth first search"
testGraph BFS
