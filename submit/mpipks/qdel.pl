use File::Copy;
use Data::Dumper;
use Cwd;
$dir = getcwd;


$id_start = 5652951;
$num_id = 100;
 

for($val = $id_start; ($val < $id_start + $num_id); $val+=1)
{
	system "qdel $val";
}