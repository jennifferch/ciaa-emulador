for dir in examples/*/
do
    echo "Building ${dir}..."
    node cli.js -i ${dir} -o outUser/ --compiler-opts "-Os"
done
