#!/usr/bin/perl
 
# The name of the file
$file = $ARGV[0];
 
# The name of the image is the body of the input path
#$name  = ($file =~ m!(w+).w+$!);
($name,$b)=split('\.',$file,2);
print $name;
# The output file name is the name of the file with the .h extension
($ofile = $file)  =~ s/.w+$//; $ofile .= ".h";
 
print "Converting image $name from $file to $ofile\n";
 
# Slurp all the input
undef $/;
open(FILE, "$file") || die "unable to open $file\n";
$in = <>;
close FILE;
 
# Open output file
open(FILE, ">$ofile") || die "unable to open $ofile for writing\n";
 
# Create an array of unsigned chars from input
@chars = unpack "C*", $in;
 
# Output
print FILE "// Automatically generated by embendimg. Not modify.\n";
print FILE "#ifndef __EMBEDIMG_${name}\n";
print FILE "#define __EMBEDIMG_${name}\n\n";
print FILE "unsigned char ${name}_img[] = {\n  ";
 
foreach $char (@chars) {
	printf FILE "0x%02x", $char;
	last if $i == $#chars;
	print FILE ((++$i % 13) ? ", " : ",\n  ");
}
 
print FILE "\n};\n\n#endif\n";
close FILE;
