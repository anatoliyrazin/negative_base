<?php

// replacement for integer modulo operator, works for negative
function mod($m, $n)
{
    if($n < 0) {
        $n = -$n;
    }
    $m %= $n;
    while($m < 0) {
        $m += $n;
    }

    return $m;
}

// replacement for integer division operator, works for negatives
function div($m, $n)
{
    $r = mod($m, $n);
    $m -= $r;

    return $m / $n;
}

// convert to decimal, works for both positive and negative radix
function to10($base, $a) {
    $n = 0;
    foreach($a as $d)
    {
        $n *= $base;
        $n += $d;
    }

    return $n;
}

// convert from decimal, works for both positive and negative radix
function from10($base, &$a, $n) {
    while($n) {
        $d = mod($n, $base);
        $n = div($n, $base);
        array_unshift($a, $d);
    }
}

// integer division, valid only for positive integers
function idiv($a, $b) {
    $a -= $a % $b;
    return $a / $b;
}

// demo for division / modulo oprations and its differences from standard integer divisions
function demoMod($a, $b) {
    echo "Demo for pair ($a, $b):\n";
    $c = $a / $b;
    $ic = idiv($a, $b);
    $d = $a % $b;

    $mc = div($a, $b);
    $md = mod($a, $b);

    echo "Standard PHP division: $a  / $b = $c\n";
    echo "Custom integer division: $a / $b = $ic\n";
    echo "Fixed integer division: $a / $b = $mc\n";
    echo "Standard PHP integer modulo: $a % $b = $d\n";
    echo "Fixed integer modulo: $a mod $b = $md\n\n";
}

// demo: convert decimal value to base $n
function demoBaseT2B($a, $n) {
    echo "Decimal $a in base $n is ";

    $v = array();
    from10($n, $v, $a);

    foreach($v as $d)
    {
        print($d);
    }
    echo "\n\n";
}

// demo: convert base $n value to decimal, $n must be between -10 and 10
function demoBaseB2T($s, $n) {
    $v = array();
    $ps = str_split($s);
    foreach($ps as $p) {
        $d = ord($p) - ord('0');
        $v[] = $d;
    }

    echo "Convert $s in base $n to decimal: " . to10($n, $v) . "\n\n";
}

// some demos for modulo
demoMod(17, 5);
demoMod(17, -5);
demoMod(-17, 5);
demoMod(-17, -5);

// some demos for conversion to and from decimal
demoBaseT2B(1000, 3);
demoBaseT2B(1000, -3);
// demoBaseT2B(-1000, 3); /* this should fail */
demoBaseT2B(-1000, -3);

demoBaseB2T("1101001", 3);
demoBaseB2T("2212001", -3);
demoBaseB2T("12101012", -3);

?>