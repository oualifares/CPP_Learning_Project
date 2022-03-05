#!/usr/bin/perl
use strict;
use warnings;

#Exo4

sub TableMult1{

    my ($n) = @_;
    for (my $i = 1; $i<$n+1 ;$i++){
        for (my $j = 1; $j<$n+1 ;$j++){
            printf('%5d',$i*$j );
        }
        print "\n";
    }
}

sub TableMult2 {
    my ($n) = @_;
    foreach my $i(1..4){
        foreach my $j(1..4){
            printf('%5d',$i*$j );
        }
        print "\n";
    }
}
#TableMult1(4);
#TableMult2(4);

sub TableMult3 {
    my ($n) = $ARGV[0];
    my ($t) = "";
    foreach my $i(1..$n){
        foreach my $j(1..$n){
           $t.=sprintf("%5d",$i*$j) ;
        }
    $t.="\n";

    }
    return $t;
}
my $res = TableMult3;
#print "$res";

#Exo5
#Recursive
sub Fact{
    my ($n) = @_;
    if($n == 0){
        return 1;
    }
    else {
        return ($n * Fact($n-1));
    }

}
$res = Fact(10);
#print "$res\n";

#Iterative
sub Fibo{
    my($n) = @_ ;
    my(@t) =(0,1);
    foreach my $i(2..$n){
        $t[$i] = $t[$i-1]+$t[$i-2];
    }
    return @t;
}

my @f = Fibo(10);


my @tab = (1,2,3); #cree un tableau contenant 4, -5 et 7
push(@tab, 4, -5); #ajoute -2 et 3`a la fin du tableau
@tab,"\n"; #Applatissement de la liste ==> 1234-5
join(", ", @tab)."\n"; #affiche le tableau (les  ́el ́ements seront séeparées par des chaˆınes virgule-espace),
unshift(@tab , 0,-1); #ajoute 0 et -1 au d ́ebut du tableau,
@tab[3] = 9; # remplace la valeur d’indice 3 par 9

#   $_ --> pour chaque element de la liste
my @s = map { $_ * 2 } @tab; #multiplie par 2 chaque terme du tableau (fonction map),
my @y = grep{$_> 0 } @tab ;# ne garde dans le tableau que les termes strictement positifs (fonction grep)


my @w = sort {$a <=> $b} @tab; #Croissant 
my @f = sort {$b <=> $a} @tab; #Decroissant 


#Exo 7
sub Intervalle{
    my($n, $x) = @_;
    my @res =(1..$n); 
    return grep{$_ != $x } @res;
}
my @res = Intervalle(10, 4);
#print "@res\n";


sub NonMult {
    my($n, $x) = @_;
    my @res =(1..$n); 
    return grep{$_ % $x!= 0 } @res;
}
my @res = NonMult(10, 2);
#print "@res\n";

#Exo8
sub primes { my ($max) = @_;
    my @candidates = (2..$max);
    my @primes = ();
    while (@candidates) {
        my $prime = shift(@candidates);
        push(@primes, $prime);
        @candidates = grep { $_ % $prime != 0 } @candidates;
    }
    return @primes;
}

my @primes = primes(@ARGV);
#print("@primes\n");

#Exo 9
sub Modif { my ($text, $old, $new) = @_;
    for (
        my $next = index($text, $old); 
        $next != -1; 
        $next = index($text, $old, $next + length($new))
    ) {
        substr($text, $next, length($old), $new);
    }

    return $text;
}

#print(Modif("bonjour vous, bonjour", "bonjour", "allo")."\n");
#print(Modif("bonjour vous, bonjour", "bonjour", "bonjour bonjour")."\n");

#TD2 EXO1:

my @arguments = @ARGV;
my %h = ('janvier'=>30,
'feverier'=>28,
'mars'=>31,
'avril'=>30,
'mai'=>31,
'juin'=>30,
'juillet'=>31,
'aout'=>31,
'septembre'=>30,
'octobre'=>31,
'novembre'=>30,
'decembre'=>31, 


);

foreach my $month(@ARGV){
    
    if(exists $h{$month}){
        print $month." : ".$h{$month}."\n";
    }else{
       print $month . " : inconnu\n";
    }
}






