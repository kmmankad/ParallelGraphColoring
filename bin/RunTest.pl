#!/usr/local/bin/perl -w

use strict;
use Getopt::Long;
use Cwd;
use Cwd 'abs_path';
use warnings FATAL => qw(all);

my %Benchmarks = (
	# Name => ["extension", "URL"]
	"thermal2" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Schmid/thermal2.tar.gz"]
);

my $binpath = "";
my $testpath = "";
my $prof = 0;

# Could use pod2usage...
sub PrintUsage {
	print "Pass path to binary with --bin=<path>\n";
}

sub RunCmd {
	my ($cmd, $log_file) = @_;
	print "## RUNNING $cmd\n";
	my $retcode;
	if ($log_file eq ""){
		$retcode = system("$cmd");
	} else {
		$retcode = system("$cmd > $log_file 2>&1");
		open (LOGFILE, $log_file);
		while(<LOGFILE>){
			print $_;
		}
		close (LOGFILE);

		my $signals  = $retcode & 127;
		my $app_exit = $retcode >> 8;
		my $dumped_core = $retcode & 0x80;
		if ($retcode != 0) {
			print "## FAILED : $cmd\n";
		} else {
			print "## PASSED $cmd\n";
		}
	}
	return $retcode;
}

sub DownloadBenchmarks(){
	foreach my $name (keys %Benchmarks){
		print "## Downloading $name...\n";
		RunCmd("wget $Benchmarks{$name}[1] -O $name.tar.gz","");
		# Unzip the guy
		RunCmd("tar -zxvf $name.tar.gz","");
		# Move the graph files out
		RunCmd("mv $name/$name\.$Benchmarks{$name}[0] ./","");
		# Delete the .tar.gz
		RunCmd("rm -rf $name/ $name.tar.gz","");
	}
}

sub RunBenchmarks(){
	foreach my $name (keys %Benchmarks){
		my $fullbinpath = abs_path($binpath);
		RunCmd("$fullbinpath $name\.$Benchmarks{$name}[0] $name\_output.txt", "$name\_run.log");
	}
}

sub SetupTestdir(){
	print "## Creating $testpath\n";
	RunCmd("mkdir -p $testpath","");
	chdir $testpath;
	print cwd;
}

sub PrintBanner(){
	print "RunTest.pl - a simple perl script to run graph benchmarks\n";
}

GetOptions('help|h' => sub { PrintUsage() and exit 0},
	'binpath=s' => \$binpath,
	'testdir=s' => \$testpath,
	'prof' => sub {$prof = 1}
);

PrintBanner();
SetupTestdir();
DownloadBenchmarks();
RunBenchmarks();
