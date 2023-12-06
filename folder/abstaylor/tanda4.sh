files=("chem.bch" "chem-1.bch" "chembis.bch")
#"ex6_2_8.bch" "ex6_1_3bis.bch" "ex6_2_12.bch" "launch.bch"
for file in ${files[@]}
do
  for seed in {1..5}
  do
    for i in {1..5}
    do
       ./__build__/src/ibexopt benchs/optim/hard/$file --random-seed=$seed >> tanda4.log
    done
  done
done