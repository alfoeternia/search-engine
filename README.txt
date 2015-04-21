USAGE: 

   ./bin/builder  [-o <string>] [-s <string>] [-c <string>] [--]
                  [--version] [-h]


Where: 

   -o <string>,  --output <string>
     Specifies an output file for the index (default:
     ./docs/index.oarchive)

   -s <string>,  --stopwords <string>
     Specifies a custom stopwords file (default ./docs/stopwords.txt).

   -c <string>,  --collection <string>
     Specifies a custom collection file (default: ./docs/cran.all.1400).

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.


   Reversed index builder

=================================================================

USAGE: 

   ./bin/search  [-p <string>] [-B <string>] [-w <string>] [-i <string>]
                 [-b] [--] [--version] [-h] <> ...


Where: 

   -p <string>,  --compute-performance <string>
     Compute performance using query-relations file (default:
     ./docs/cranqrel)

   -B <string>,  --bulk <string>
     Bulk process queries file (default: ./docs/cran.qry)

   -w <string>,  --stopwords <string>
     Specifies a custom stopwords file (default: ./docs/stopwords.txt)

   -i <string>,  --index <string>
     Specify index file (default: ./docs/index.oarchive)

   -b,  --binary
     Performs a binary search

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.

   <>  (accepted multiple times)
     Queries


   Search engine

