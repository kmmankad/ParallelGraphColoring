#!/usr/local/bin/perl -w

use strict;
use Getopt::Long;
use Cwd;
use File::Spec;
use warnings FATAL => qw(all);

my %Benchmarks = (
	# Name => ["extension", "URL"]
## From UFlorida Sparse Matrix collection
	"afshell_3" => ["mtx", "https://www.cise.ufl.edu/research/sparse/MM/Schenk_AFE/af_shell3.tar.gz"],
	"parabolic_fem" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Wissgott/parabolic_fem.tar.gz"],
	"apache2" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/GHS_psdef/apache2.tar.gz"],
	"ecology2" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/McRae/ecology2.tar.gz"],
	"thermal2" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Schmid/thermal2.tar.gz"],
	"G3_circuit" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/AMD/G3_circuit.tar.gz"],
	"FEM_3D_thermal2" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Botonakis/FEM_3D_thermal2.tar.gz"],
	"thermomech_dK" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Botonakis/thermomech_dK.tar.gz"],
	"ASIC_320ks" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Sandia/ASIC_320ks.tar.gz"],
	"cage13" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/vanHeukelum/cage13.tar.gz"],
	"atmosmodd" => ["mtx", "http://www.cise.ufl.edu/research/sparse/MM/Bourchtein/atmosmodd.tar.gz"]
## From DIMACS
	### TODO
);

my $binpath = "";
my $testpath = "";
my $onlyrun = "";
# TODO: Add profiler stat collection support
my $prof = 0;

# Could use pod2usage...
sub PrintUsage {
	print "Usage: \n";
	print "Pass path to binary with --binpath=<path>\n";
	print "Pass test-run directory (will be created) with --testdir=<folder-path>\n";
	print "Pass the --only <name> to run only a specific benchmark by name\n";
}

###################################
# Subroutine to run a command and
# save the output to a log file
#
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

###########################################
# Subrotuine to download a named benchmark
#
sub DownloadBenchmark {
	my $BenchmarkName = shift @_;
	if (exists ($Benchmarks{$BenchmarkName})){
		print "## Downloading $BenchmarkName...\n";
		RunCmd("wget $Benchmarks{$BenchmarkName}[1] -O $BenchmarkName.tar.gz","");
		# Unzip the guy
		RunCmd("tar -zxvf $BenchmarkName.tar.gz","");
		# Move the graph files out (by appropriate extension)
		RunCmd("mv $BenchmarkName/$BenchmarkName\.$Benchmarks{$BenchmarkName}[0] ./","");
		# Delete the .tar.gz
		RunCmd("rm -rf $BenchmarkName/ $BenchmarkName.tar.gz","");
	} else {
		die("Benchmark name $BenchmarkName not found! ABORTING. \n");
	}
}

##########################################
# Subroutine to download all benchmarks
#
sub DownloadBenchmarks(){
	my $NumBenchmarks = scalar(keys(%Benchmarks));
	print "## Running ALL $NumBenchmarks Benchmarks!\n";
	foreach my $name (keys %Benchmarks){
		DownloadBenchmark($name);
	}
}

###########################################
# Subroutine to run a named benchmark
#
sub RunBenchmark {
	my $BenchmarkName = shift @_;
	my $fullbinpath = "";
	if ($binpath eq ""){
		die("No --binpath passed! ABORTING. \n");
	} else {
		$fullbinpath = File::Spec->rel2abs($binpath,"..");
		if ( -X $fullbinpath){
			RunCmd("$fullbinpath $BenchmarkName\.$Benchmarks{$BenchmarkName}[0] $BenchmarkName\_output.txt", "$BenchmarkName\_run.log");
		} else {
			die("$fullbinpath is not executable! ABORTING. \n");
		}
	}
}

###########################################
# Subroutine to run all benchmarks
#
sub RunBenchmarks(){
	foreach my $name (keys %Benchmarks){
		RunBenchmark($name);
	}
}

###########################################
# Subroutine to create the test dir
#
sub SetupTestdir(){
	if ($testpath ne ""){
		print "## Creating $testpath\n";
		RunCmd("mkdir -p $testpath","");
		chdir $testpath;
		print cwd;
	} else {
		die ("No --testdir passed! ABORTING. \n");
	}
}

###########################################
# Subroutine to print the welcome banner
#
sub PrintBanner(){
	print "/---------------------------------------------------------\\\n";
	print "|RunTest.pl - a simple perl script to run graph benchmarks|\n";
	print "\\---------------------------------------------------------/\n";
}

GetOptions('help|h' => sub { PrintUsage() and exit 0},
	'binpath=s' => \$binpath,
	'testdir=s' => \$testpath,
	'only=s' => \$onlyrun,
	'prof' => sub {$prof = 1}
);

PrintBanner();
SetupTestdir();
if ($onlyrun ne ""){
	DownloadBenchmark($onlyrun);
	RunBenchmark($onlyrun);
}else{
	DownloadBenchmarks();
	RunBenchmarks();
}
