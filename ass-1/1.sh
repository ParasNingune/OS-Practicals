echo "Assignment-1\n
Program to create an address book"

opt=1
# read -p "Enter file name (New/Existing): " fileName
fileName="address.txt"

while [ "$opt" -lt 6 ]
do 
    echo "\n\n"
    echo "Choose one of the following:\n1. Create New Address Book\n2. View Records\n3. Insert Record\n4. Delete Record\n5. Update Record\n6. Exit"
    read -p "Enter your choice: " opt

    case $opt in

    1)
        read -p "Enter fileName to create: " newFileName
        newFileName="$newFileName.txt"
        echo $newFileName
        if [ ! -f "$newFileName" ]; 
            then
                touch "$newFileName"
                echo "New Address Book created successfully"
                echo "Name\t\tRollNo\tAge\tCity\n" | cat >> $newFileName
        else
            echo "File already exists"
        fi

            cnt=1
            while [ $cnt -gt 0 ]
                do
                    echo "\n"
                    read -p "Enter name of Student: " name
                    read -p "Enter roll no of Student: " roll
                    read -p "Enter age of Student: " age
                    read -p "Enter city of Student: " city
                    echo "$name\t\t$roll\t$age\t$city" | cat >> $fileName

                    echo "\n\nName: $name\nRoll No: $roll\nAge: $age\nCity: $city\nEntered in the file!!!!\n\n"
                    echo "Enter 1 for Next\nEnter 0 to Stop"
                    read -p "Enter your choice: " cnt
                done
            echo "\n\n"
        ;;
    
    2) 
        echo "\n"
        cat $fileName
        ;;
    
    3)
        echo "\n"
        read -p "Enter name of Student: " name
        read -p "Enter roll no of Student: " roll
        read -p "Enter age of Student: " age
        read -p "Enter city of Student: " city
        echo "$name\t\t$roll\t$age\t$city" | cat >> $fileName

        echo "\n\nName: $name\nRoll No: $roll\nAge: $age\nCity: $city\nEntered in the file!!!!"
        ;;

    4) 
        echo "\nDelete Record"
        read -p "Enter Name/Roll No: " pattern
        temp="temp"
        grep -v $pattern $fileName | cat >> $temp
        rm $fileName
        cat $temp | cat >> $fileName
        rm $temp
        echo "Removed $pattern from Address Book\n"
        cat $fileName
        ;;

    5)
        echo "\nUpdate Record"
        read -p "Enter Name/Roll No: " pattern
        temp="temp"
        grep -v $pattern $fileName | cat >> $temp
        rm $fileName
        cat $temp | cat >> $fileName
        rm $temp
        echo "\n"
        read -p "Enter name of Student: " name
        read -p "Enter roll no of Student: " roll
        read -p "Enter age of Student: " age
        read -p "Enter city of Student: " city

        echo "$name\t\t$roll\t$age\t$city" | cat >> $fileName

        echo "Name: $name\nRoll No: $roll\nAge: $age\nCity: $city\nUpdated in the file!!!"
        ;;

    6)
        echo "Exit\n\n"
        ;;
    
    esac
done