set ns [new simulator]

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish{}{
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}


set n0 [$ns node]






$ns duplex-link $n0 $n1 1Mb 10ms DropTail







set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$ns attach-agent $n1 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n4s $sink0

$ns connect $tcp0 $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.01
$ns attach-agent $cbr0

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"
$ns at 5.0 "$cbr0 finish"


$ns run
