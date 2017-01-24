
graph g
set v1 [g vertex]
set v2 [g vertex]
set v3 [g vertex]

VertexList vertices
vertices insert [$v3 reference]
vertices insert [$v2 reference]
vertices insert [$v1 reference]

proc foo {vertex} {
	puts "vertex [$vertex id] is at [$vertex reference]"
}
vertices map foo

vertices destroy
