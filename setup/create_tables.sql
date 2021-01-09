
USE free_budget_db; -- the web app expects the database to be named this 


--uploaded files
CREATE TABLE uploaded_files (
	upload_id INT AUTO_INCREMENT PRIMARY KEY,
	upload_date DATE NOT NULL,
	upload_file_name VARCHAR(255) NOT NULL
);

CREATE TABLE imported_data (
	import_line_id INT AUTO_INCREMENT PRIMARY KEY,
	upload_id INT NOT NULL,
	transaction_date DATE NOT NULL,
	src_bank_account VARCHAR(200) NOT NULL,
	description VARCHAR(500) NOT NULL,
	amount DECIMAL(15,2) NOT NULL,
	correlated_flag BIT NOT NULL,
	
	INDEX upload_id_to_upload (upload_id),
	FOREIGN KEY (upload_id)
	    REFERENCES uploaded_files(upload_id)
);


--accounting tables 
CREATE TABLE accounting_books (
	book_id INT AUTO_INCREMENT PRIMARY KEY,
	book_name VARCHAR(50) NOT NULL
);

CREATE TABLE accounting_account_type (
	account_type_id INT AUTO_INCREMENT PRIMARY KEY,
	account_type_description VARCHAR(50) NOT NULL
);

--static account types from double entry accounting
INSERT INTO accounting_account_type (account_type_description) VALUES ('asset');
INSERT INTO accounting_account_type (account_type_description) VALUES ('liability');
INSERT INTO accounting_account_type (account_type_description) VALUES ('equity');
INSERT INTO accounting_account_type (account_type_description) VALUES ('revenue');
INSERT INTO accounting_account_type (account_type_description) VALUES ('expense');

CREATE TABLE accounting_line_type (
	line_type_id INT AUTO_INCREMENT PRIMARY KEY,
	line_type_description VARCHAR(20) NOT NULL
);

--static line types 
INSERT INTO accounting_line_type (line_type_description) VALUES ('debit');
INSERT INTO accounting_line_type (line_type_description) VALUES ('credit');

--budget side category
CREATE TABLE budget_categories (
	category_id INT AUTO_INCREMENT PRIMARY KEY,
	category VARCHAR(100) NOT NULL,
	description VARCHAR(255) NULL
);


CREATE TABLE accounting_accounts (
	account_id INT AUTO_INCREMENT PRIMARY KEY,
	rel_accounting_book_id INT NOT NULL,
	rel_account_type_id INT NOT NULL,
	rel_category_id INT NOT NULL,
	account_name VARCHAR(150) NOT NULL,
	description VARCHAR(500) NULL
);

ALTER TABLE accounting_accounts ADD
FOREIGN KEY (rel_accounting_book_id)
	    REFERENCES accounting_books(book_id);

ALTER TABLE accounting_accounts ADD
FOREIGN KEY (rel_account_type_id)
	REFERENCES accounting_account_type(account_type_id);
		
ALTER TABLE accounting_accounts ADD 
FOREIGN KEY (rel_category_id)
	REFERENCES budget_categories(category_id);


-- entries are made up of lines, 
-- each line is related to an account
-- entry_id should be client generated
CREATE TABLE accounting_entries (
	entry_id INT PRIMARY KEY, 
	rel_book_id INT NOT NULL,
	entered DATE NOT NULL
);

ALTER TABLE accounting_entries ADD
FOREIGN KEY (rel_book_id)
	    REFERENCES accounting_books(book_id);
		
--entries are made up of lines 
--follow double entry accounting in that 
--total credits must = total debits for an entry to 
--be valid 
CREATE TABLE accounting_lines (
	line_id INT AUTO_INCREMENT PRIMARY KEY,
	rel_accounting_entry_id INT NOT NULL,
	rel_account_id INT NOT NULL,
	rel_line_type_id INT NOT NULL,
	memo VARCHAR(250) NULL,
	amount DECIMAL(15,2) NOT NULL
);

ALTER TABLE accounting_lines ADD
FOREIGN KEY (rel_accounting_entry_id)
	    REFERENCES accounting_entries(entry_id);
		
ALTER TABLE accounting_lines ADD
FOREIGN KEY (rel_account_id)
	    REFERENCES accounting_accounts(account_id);

ALTER TABLE accounting_lines ADD
FOREIGN KEY (rel_line_type_id)
	    REFERENCES accounting_line_type(line_type_id);

		

--correlation table (links uploads to accounting)



--budget info (links accounting to budget part)
CREATE TABLE budgets (
	id INT AUTO_INCREMENT PRIMARY KEY,
	budget_name VARCHAR(50) NOT NULL
);

CREATE TABLE budget_targets (
	budget_target_id INT AUTO_INCREMENT PRIMARY KEY,
	assoc_budget_id INT NOT NULL,
	rel_category_id INT NOT NULL,
	target_amount DECIMAL(15,2) NOT NULL
);

ALTER TABLE budget_targets ADD 
FOREIGN KEY (assoc_budget_id)
	REFERENCES budgets(id);

ALTER TABLE budget_targets ADD 
FOREIGN KEY (rel_category_id)
	REFERENCES budget_categories(category_id);
	

	
	
