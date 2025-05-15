<!DOCTYPE html>
<html lang="en">
<head>
    <title>Modify Information</title>
</head>
<body>

    <?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "DB2";

    // Establish connection
    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["student_id"])) {
        $student_id = (string)$_POST["student_id"];
    }
    $type = "student";
    $dept_name = "Miner School of Computer & Information Sciences"; 
    ?>

    <!-- Student Information Form -->
    <h1>Student Update</h1>
    <form action="modify.php" method="post">
        <input type="hidden" name="student_id" value="<?php echo $student_id; ?>">

        <label for="email">Email:</label>
        <input type="text" name="email" id="email" required><br><br>

        <label for="password">Password:</label>
        <input type="text" name="password" id="password" required><br><br>

        <input type="hidden" name="type" value="<?php echo $type; ?>">

        <label for="name">Name:</label>
        <input type="text" name="name" id="name" required><br><br>

        <input type="hidden" name="dept_name" value="<?php echo $dept_name; ?>">

        <button type="submit">Update</button>
    </form>

    <?php $conn->close(); ?>
</body>
</html>