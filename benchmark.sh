


#!/bin/bash

make all
./ft_containers > ft_output
./std_containers > std_output
diff ft_output std_output
rm ft_output std_output