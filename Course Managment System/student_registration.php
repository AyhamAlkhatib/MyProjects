<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = $_POST["student_id"];
    $name = $_POST["name"];
    $email = $_POST["email"];
    $class_standing = $_POST["class_standing"];
    $dept_name = "Miner School of Computer & Information Sciences";
    
    $sql = $conn->query("INSERT INTO student (student_id, name, email, dept_name, standing) 
            VALUES ('$student_id', '$name', '$email', '$dept_name', '$class_standing')");
    
    if ($class_standing == "Undergraduate") {
        echo "Information saved Succefully!";
        $ug = $conn->query("INSERT INTO undergraduate (student_id, total_credits, class_standing) 
           VALUES ('$student_id', 0, 'Freshman')");
    } else if ($class_standing == "Master") {
        $master = $conn->query("INSERT INTO master (student_id, total_credits) 
           VALUES ('$student_id', 0)");
        echo "Information saved Succefully!";
    } else {
        $qualifier = "Incomplete";
        $PhD = $conn->query("INSERT INTO PhD (student_id, qualifier) 
           VALUES ('$student_id', '$qualifier')");
        echo "Information saved Succefully!";
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>

<head>
    <title>Student Registration</title>
</head>
<body>
    <br><br>
    <a href="main.html"><button>Main Page</button></a>
</body>

</html>