
CREATE TABLE investors (
pk_investor INTEGER PRIMARY KEY,

name TEXT,
email TEXT,
description TEXT,
date_of_inclusion TEXT /* sqlite 3 does not have a date dataype (sept/16) */
);

CREATE TABLE subjects (
pk_subject INTEGER PRIMARY KEY,

tag TEXT, /* (project, subproject, task type, whatever) */
description TEXT,
date_of_inclusion TEXT
);

CREATE TABLE currencies (
pk_currency INTEGER PRIMARY KEY,

label TEXT,
description TEXT,
date_of_inclusion TEXT
);

CREATE TABLE invested_time (
pk_invested_time INTEGER PRIMARY KEY,
fk_investor INTEGER,
fk_currency INTEGER,

date TEXT,
description TEXT,
comment TEXT,
minutes INTEGER,
price_per_unit REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency)
);

CREATE TABLE invested_time_subjects_link (
fk_invested_time INTEGER,
fk_subject INTEGER,

PRIMARY KEY (fk_invested_time, fk_subject),
FOREIGN KEY(fk_invested_time) REFERENCES invested_time(pk_invested_time),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE invested_assets (
pk_invested_asset INTEGER PRIMARY KEY,
fk_investor INTEGER,
fk_currency INTEGER,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
price REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency)
);

CREATE TABLE invested_assets_subjects_link (
fk_invested_asset INTEGER,
fk_subject INTEGER,

PRIMARY KEY (fk_invested_asset, fk_subject),
FOREIGN KEY(fk_invested_asset) REFERENCES invested_assets(pk_invested_asset),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE bonuses (
pk_bonus INTEGER PRIMARY KEY,
fk_investor INTEGER,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
reward TEXT,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor)
);

CREATE TABLE bonuses_subjects_link (
fk_bonus INTEGER,
fk_subject INTEGER,

PRIMARY KEY (fk_bonus, fk_subject),
FOREIGN KEY(fk_bonus) REFERENCES bonuses(pk_bonus),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE invested_money (
pk_invested_money INTEGER PRIMARY KEY,
fk_investor INTEGER,
fk_currency INTEGER,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
amount REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency)
);

CREATE TABLE invested_money_subjects_link (
fk_invested_money INTEGER,
fk_subject INTEGER,

PRIMARY KEY (fk_invested_money, fk_subject),
FOREIGN KEY(fk_invested_money) REFERENCES invested_money(pk_invested_money),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

