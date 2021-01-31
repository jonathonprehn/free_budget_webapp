<!-- This page is loaded into manageCategories.php using jQuery's load() function -->
<div class="row">
	<div class="col-12">
		<h5>Existing accounts</h5>
		<table class="table">
		<tr>
			<th>Account Name</th>
			<th>Account Type</th>
			<th>Budget Category</th>
			<th>Description</th>
			<th>Total Debits</th>
			<th>Total Credits</th>
			<th>Balance</th>
			<td></th>
		</tr>
		<?php
		$account_book_id = "1"; //TODO: figure out how to select book id
		$account_query = "select a.account_id, a.account_name, a.description, t.account_type_description, b.category "
				 ."from accounting_accounts as a "
				 ."left join accounting_account_type as t on a.rel_account_type_id = t.account_type_id  "
				 ."left join budget_categories as b on a.rel_category_id = b.category_id "
				 ." where a.rel_accounting_book_id = ".$account_book_id.";";
		$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
		if (mysqli_connect_error()) {
			die("Failed to connect to db: " . mysqli_connect_error());
		}
		try {
			$sel = $conn->query($account_query);
			while($row = $sel->fetch_assoc()) {
				echo "<tr>";

				//account name
				echo "<td>";
				echo "".$row["account_name"]."";
				echo "</td>";

				//account type
				echo "<td>";
				echo "".$row["account_type_description"]."";
				echo "</td>";

				//budget category
				echo "<td>";
				echo "".$row["category"]."";
				echo "</td>";

				//account description
				echo "<td>";
				echo "".$row["description"]."";
				echo "</td>";

				//total debits
				echo "<td>";
				echo "";
				echo "</td>";

				//total credits
				echo "<td>";
				echo "";
				echo "</td>";

				//balance
				echo "<td>";
				echo "";
				echo "</td>";

				//delete button
				echo "<td>";
				echo "";
				echo "</td>";

				echo "</tr>";	
			}
		} catch(Exception $e) {
			echo "Error getting accounts: " . $e->getMessage();
		}
		?>
		</table>
		
	</div>
</div>

