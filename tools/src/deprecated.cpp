

/* Write data to fasta file */

// [[Rcpp::export]]
void write_fasta( Rcpp::CharacterVector seq,
                  std::string seqname, 
                  std::string filename, 
                  int rowlength=80,
                  int verbose=1) {
//  rowlength=rowlength-1;
  FILE * pFile;
//  pFile=fopen(filename.c_str(),"wt");
  pFile=fopen(filename.c_str(),"at");
  int i = 0;
//  unsigned int i = 0;
  
  if(verbose == 1){
    Rcpp::Rcout << "Processing sample: " << seqname << "\n";
  }

  putc ('>' , pFile);
  for(i=0; (unsigned)i<seqname.size(); i++){
    putc (seqname[i] , pFile);
  }
  putc ('\n' , pFile);

  putc (Rcpp::as< char >(seq[0]) , pFile);
  for(i=1; i<seq.size(); i++){
    Rcpp::checkUserInterrupt();
//    putc (seq[i][0] , pFile);
    if( i % rowlength == 0){
      putc('\n', pFile);
    }
    putc (Rcpp::as< char >(seq[i]) , pFile);
    if(i % nreport == 0 && verbose == 1){
      Rcpp::Rcout << "\rNucleotide " << i << " processed";
    }
  }
  putc('\n', pFile);
  fclose (pFile);
  if(verbose == 1){
    Rcpp::Rcout << "\rNucleotide " << i << " processed\n";
  }
//  return 0;
}



