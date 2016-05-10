
graph g
set v0 [g vertex]
set v1 [g vertex]
set v2 [g vertex]
set v3 [g vertex]

VertexQueue q
q enqueue [$v1 reference]
q enqueue [$v3 reference]
q enqueue [$v0 reference]
q enqueue [$v2 reference]

if { [q dequeue] != $v1 } {
    error "dequeued wrong vertex"
}
if { [q dequeue] != $v3 } {
    error "dequeued wrong vertex"
}
if { [q dequeue] != $v0 } {
    error "dequeued wrong vertex"
}
if { [q dequeue] != $v2 } {
    error "dequeued wrong vertex"
}
puts "dequeued in correct order"

switch [catch {q dequeue} value] {
    0 {
        error "catch should have had error from empty queue"
    }
    default {
        if { $value != "queue is empty" } {
            error "dequque did not handle empty correctly ($value)"
        }
        puts "VertexQueue produced correct error from empty queue"
    }
}

exit 0

# vim:autoindent expandtab
