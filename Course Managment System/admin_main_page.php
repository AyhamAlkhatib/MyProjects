<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Admin Main Page</title>
</head>
<body>
    <h1>Welcome, Admin!</h1>

    <table border="1">
        <tr>
            <td><a href="add_section.html"><button type="button">Add Section</button></a></td>
        </tr>
        <tr>
            <td><a href="show_courses_TA.php"><button type="button">Assign TA</button></a></td>
        </tr>
        <tr>
            <td><a href="show_courses_grader.php"><button type="button">Assign Grader</button></a></td>
        </tr>
        <tr>
            <td><a href="show_students_advise.php"><button type="button">Assign Advise</button></a></td>
        </tr>
        <tr>
            <td>
                <form action="main.html" method="post">
                    <button type="submit">Sign Out</button>
                </form>
            </td>
        </tr>
    </table>
</body>
</html>