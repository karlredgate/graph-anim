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


set radius 8

graph g

frame .top
frame .bottom
pack .top .bottom

text .log
scrollbar .sb -orient vert

pack .sb .log -expand yes -fill both -side right -in .top
.log conf -yscrollcommand {.sb set}
.sb conf -command {.log yview}

button .dfs -text "DFS" -command {g DFS}
button .bfs -text "BFS" -command {g BFS}
pack .dfs .bfs -side left -in .bottom

.log insert end "left click to create vertex.
right click and drag to create edge between vertices.
double left click to traverse graph.
-----------------------------------------------------
"
proc log {msg} {
    .log insert end "> $msg\n"
    .log see end
}

set c [canvas .c]
pack $c -expand yes -fill both -in .top

# bind $c <1>         "grab $c %x %y"
# bind $c <B1-Motion> "drag $c %x %y"

bind $c <Double-ButtonPress-1> "DFS $c %x %y"
bind $c <ButtonPress-1> "grab_or_vertex $c %x %y"
bind . v "draw_vertex $c %x %y"
bind . q "exit"

proc closest_oval {c x y} {
    global radius
    set x1 [expr $x-$radius]
    set y1 [expr $y-$radius]
    set x2 [expr $x+$radius]
    set y2 [expr $y+$radius]
    set items [$c find overlapping $x1 $y1 $x2 $y2]
    foreach item $items {
        set type [$c type $item]
        if { $type == "oval" } break
    }
    if { $type == "oval" } { return $item }
    log "Type of '$item' is '$type'"
    return {}
}

proc grab_or_vertex {c x y} {
    global radius
    set x1 [expr $x-$radius]
    set y1 [expr $y-$radius]
    set x2 [expr $x+$radius]
    set y2 [expr $y+$radius]
    set near [$c find overlapping $x1 $y1 $x2 $y2]
    if { [llength $near] > 1 } {
        log "More than one item near cursor"
        return
    }
    log "Type of '$near' is '[$c type $near]'"
    if { [$c type $near] != "oval" } {
        draw_vertex $c $x $y
    } else {
        log "Grab should happen"
    }
}

proc draw_vertex {c x y} {
    global radius

    set x1 [expr $x-$radius]
    set y1 [expr $y-$radius]
    set x2 [expr $x+$radius]
    set y2 [expr $y+$radius]

    set u [$c create oval $x1 $y1 $x2 $y2 -fill yellow -activefill green]
    $c bind $u <1>         "grab $c %x %y"
    $c bind $u <B1-Motion> "drag $c %x %y"

    $c bind $u <ButtonPress-3>         "startLine $c %x %y"
    $c bind $u <B3-Motion> "moveLine $c %x %y"
    $c bind $u <ButtonRelease-3> "finishline $c %x %y"

    set label [g vertex]

    $c create text $x1 [expr $y2+2] -text $label -anchor nw
    $c addtag $label withtag $u

    # $label enter "$c itemconfigure $u -fill blue ; puts \"Enter: $label ($u)\""
    Advice tracer
    tracer enter "$c itemconfigure $u -fill blue"
    tracer visit "log \"visit $label (id=$u)\""
    tracer leave "$c itemconfigure $u -fill yellow"
    $label advice [tracer]
    # $label leave "$c itemconfigure $u -fill yellow ; puts \"Leave: $label ($u)\""
}

proc centerpoint {coords} {
    foreach {x1 y1 x2 y2} $coords {}
    set x [expr $x1+(($x2-$x1)/2)]
    set y [expr $y1+(($y2-$y1)/2)]
    return [list $x $y]
}

proc getvertex {c tagOrId} {
    set tags [$c gettags $tagOrId]
    foreach tag $tags {
        if { $tag == "current" } continue
        return $tag
    }
    log "No vertex for $tagOrId"
    exit
}

proc startLine {c x y} {
    global U V
    set U [getvertex $c current]
    set V ""

    global edge edgeU edgeV
    set edgeU [centerpoint [$c coords current]]
    set edgeV "$x $y"
    set coords [concat $edgeU $edgeV]
    set edge [$c create line $coords -arrow last]
}

proc finishline {c x y} {
    global edge edgeU edgeV

    set end "$x $y"
    # set closest [$c find closest $x $y]
    set closest [closest_oval $c $x $y]
    set type    [$c type $closest]
    if { $type != "oval" } {
        log "Closest item is not an oval, it is a '$type'"
        $c delete $edge
        return
    }
    set here [centerpoint [$c coords $closest]]
    $c coords $edge [concat $edgeU $here]

    global U V
    set V [getvertex $c $closest]
    set edge_cmd [$U connect [$V reference]]
    # $edge_cmd enter "$c itemconfigure $edge -fill red ; puts \"enter $edge_cmd\""
    Advice tracer
    tracer enter "$c itemconfigure $edge -fill red"
    tracer visit "log \"visit $edge_cmd (id=$edge)\""
    tracer leave "$c itemconfigure $edge -fill black"
    $edge_cmd advice [tracer]
    # $edge_cmd leave "$c itemconfigure $edge -fill black ; puts \"leave $edge_cmd\""
}

proc DFS {c x y} {
    set closest [closest_oval $c $x $y]
    set V [getvertex $c $closest]
    set DAG [g DFS [$V reference]]
    log "Graph is $DAG"
}

proc moveLine {c x y} {
    global edge edgeU edgeV
    set edgeV "$x $y"
    $c coords $edge [concat $edgeU $edgeV]
}

proc grab {c x y} {
    global lastX lastY
    set lastX [$c canvasx $x]
    set lastY [$c canvasy $y]
    $c raise current
}

proc drag {c x y} {
    global lastX lastY
    set x [$c canvasx $x]
    set y [$c canvasy $y]
    $c move current [expr {$x-$lastX}] [expr {$y-$lastY}]
    set lastX $x
    set lastY $y
}
