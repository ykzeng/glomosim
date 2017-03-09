#!/bin/bash

protocols=('DSR' 'AODV')
pauses=('2S' '5S' '10S' '20S')

# iterate through all protocols
for protocol in "${protocols[@]}"
do
  echo "=======================$protocol======================" >> raw_data.txt
  # using different routing protocols
  sed -i '277s/ROUTING-PROTOCOL\ .*/ROUTING-PROTOCOL\ '$protocol'/g' config.in.bak
  echo 'Current iteration protocol: '$protocol''
  # iterate through all pauses
  for pause in "${pauses[@]}"
  do
    # array for stream avg data of each seed
    received_pause=(0 0 0 0 0)
    
    delay_pause=(0 0 0 0 0)
    echo "--------------------PAUSE $pause---------------------" >> raw_data.txt
    # test different PAUSE time
    sed -i '124s/MOBILITY-WP-PAUSE\ .*/MOBILITY-WP-PAUSE\ '$pause'/g' config.in.bak
    echo 'Current iteration pause: '$pause''
    # do random seed from 1 to 5
    for seed in {1..5}
    do
      stream_received=(0 0 0 0 0)
      stream_delay=(0 0 0 0 0)
      echo "SEED $seed" >> raw_data.txt
      echo -e "Received\t Avg Delay" >> raw_data.txt

      sed -i '60s/SEED\ .*/SEED\ '$seed'/g' config.in.bak
      echo 'Current iteration seed: '$seed''
      # run the simulation assuming that every config is set
      ../glomosim config.in.bak
      # read the file and find all the data we need
      last=0
      delay=0
      stream_num=0
      # read all lines in current glomo.stat and read out packets delay stat
      while read line; do
       # data for PDR
       if [[ $line == *"Total number of packets received: "* ]] ; then 
         #echo "$line"
         IFS=':' read -ra ADDR <<< "$line"
         last=${#ADDR[@]}
         last=$((last - 1))
         # received packets of stream in array
         stream_received[$stream_num]=${ADDR[$last]}
# TODO compute per seed avg
# TODO compute per pause avg based on per stream
         #echo "array size: '$last'" 
         #echo "target data: ${ADDR[$last]}"
       # data for end-to-end delay
       elif [[ $line == *"end-to-end"* ]] ; then 
         # we got a new stream
         stream_num=$(($stream_num + 1))
         IFS=':' read -ra ADDR <<< "$line"
         last=${#ADDR[@]}
         last=$((last - 1))
         # delay of stream in array
         stream_delay[$stream_num]=${ADDR[$last]}
         delay_pause[$seed]=$delay
       fi
      done<glomo.stat

      # iterate all streams and output the result
      # also compute the avg result
      s_rec_avg=0
      s_del_avg=0
      for s_index in {1..5}
      do
        received=${stream_received[$s_index]}
        delay=${stream_delay[$s_index]}

        part_sum_rec=$(echo "scale=5;$s_rec_avg * ($s_index - 1) + $received"|bc)
        part_sum_del=$(echo "scale=5;$s_del_avg * ($s_index - 1) + $delay"|bc)
        
        s_rec_avg=$(echo "scale=5;$part_sum_rec / $s_index"|bc)
        s_del_avg=$(echo "scale=5;$part_sum_del / $s_index"|bc)
        #s_rec_avg=$(echo "scale=5;(($s_rec_avg * ($s_index - 1) + $received) /
        #$s_index)"|bc)
        #s_del_avg=$(echo "scale=5;((($s_del_avg * ($s_index - 1)) + $delay) /
        #$s_index)"|bc)
        echo -e "${received}\t $delay" >> raw_data.txt
      done
      echo -e "Avg rec per s\t $s_rec_avg" >> raw_data.txt
      echo -e "Avg del per s\t $s_del_avg" >> raw_data.txt
      echo "" >> raw_data.txt
      
      # save stream avg data to seed avg array
      received_pause[$seed]=$s_rec_avg
      echo "save received pause: ${received_pause[$seed]}"
      delay_pause[$seed]=$s_del_avg
      echo "save delay pause: ${delay_pause[$seed]}"
      # per stream iteration ends here
    done
    sum_delay=0
    sum_received=0
    for j in {1..5}
    do
      echo "received pause: ${received_pause[$seed]}"
      echo "delay pause: ${delay_pause[$seed]}"
      sum_received=$(echo "scale=5;${received_pause[$j]} + $sum_received"|bc)
      #sum_delay=$((${delay_pause[$j]} + $sum_delay))
      sum_delay=$(echo "scale=5;${delay_pause[$j]} + $sum_delay"|bc)
    done
    #avg_received_pause=$(echo "$sum_received + $b" | bc)
    avg_received=$(echo "scale=5;$sum_received / 5"|bc)
    avg_delay=$(echo "scale=5;$sum_delay / 5"|bc)
    echo -e "Sum received:\t$sum_received" >> raw_data.txt
    echo -e "Sum delay:\t$sum_delay" >> raw_data.txt
    echo -e "Avg received:\t$avg_received" >> raw_data.txt
    echo -e "Avg delay:\t$avg_delay" >> raw_data.txt
    # seed wise test ends here
  done
  # pause wise test ends here
done
