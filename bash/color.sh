#!/bin/bash
for i in {1..10}; do
	echo "\033[0;$im_hello_\033[0m"
	printf "\033[0;$im_hello_\033[0m\n"
done

echo "\033[0;$(i)m_hello_\033[0m\n"
printf "\033[0;$(i)m_hello_\033[0m\n"
