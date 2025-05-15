<?php
$instructor_id = isset($_GET['instructor_id']) ? $_GET['instructor_id'] : null;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Instructor Page</title>
</head>
<body>
    <h1>Welcome, Instructor!</h1>

    <table border="1">
        <tr>
            <td>
                <form action="instructor_course_history.php" method="post">
                    <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">
                    <button type="submit">View Course History</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="show_studentid_for_course_history.php" method="post">
                    <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">
                    <button type="submit">View Advise Course History</button>
                </form>
            </td>
        </tr>
            <td>
                <a href="show_students_advise.php"><button type="button">Assign Advise</button></a>
            </td>
        </tr>
        <tr>
            <td>
                <form action="show_students_advise_to_modify.php" method="post">
                    <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">
                    <button type="submit">Modify Advise Information</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="main.html" method="post">
                    <button type="submit">Sign Out</button>
                </form>
            </td>
        </tr>
        <tr>
    </table>
</body>
</html>