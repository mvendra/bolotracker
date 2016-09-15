
CREATE TABLE investors (
pk_investor INTEGER PRIMARY KEY NOT NULL,

name TEXT NOT NULL,
email TEXT,
description TEXT,
date_of_inclusion TEXT,
UNIQUE(pk_investor, name)
);

CREATE TABLE subjects (
pk_subject INTEGER PRIMARY KEY NOT NULL,

tag TEXT NOT NULL,
description TEXT,
date_of_inclusion TEXT,
UNIQUE(pk_subject, tag)
);

CREATE TABLE currencies (
pk_currency INTEGER PRIMARY KEY NOT NULL,

label TEXT NOT NULL,
description TEXT,
date_of_inclusion TEXT,
UNIQUE(pk_currency, label)
);

CREATE TABLE invested_time (
pk_invested_time INTEGER PRIMARY KEY NOT NULL,
fk_investor INTEGER NOT NULL,
fk_currency INTEGER NOT NULL,

date TEXT,
description TEXT,
comment TEXT,
minutes INTEGER,
price_per_unit REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),
UNIQUE(pk_invested_time)
);

CREATE TABLE invested_time_subjects_link (
fk_invested_time INTEGER NOT NULL,
fk_subject INTEGER NOT NULL,

PRIMARY KEY (fk_invested_time, fk_subject),
FOREIGN KEY(fk_invested_time) REFERENCES invested_time(pk_invested_time),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE invested_assets (
pk_invested_asset INTEGER PRIMARY KEY NOT NULL,
fk_investor INTEGER NOT NULL,
fk_currency INTEGER NOT NULL,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
price REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),
UNIQUE(pk_invested_asset)
);

CREATE TABLE invested_assets_subjects_link (
fk_invested_asset INTEGER NOT NULL,
fk_subject INTEGER NOT NULL,

PRIMARY KEY (fk_invested_asset, fk_subject),
FOREIGN KEY(fk_invested_asset) REFERENCES invested_assets(pk_invested_asset),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE bonuses (
pk_bonus INTEGER PRIMARY KEY NOT NULL,
fk_investor INTEGER NOT NULL,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
reward TEXT,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
UNIQUE(pk_bonus)
);

CREATE TABLE bonuses_subjects_link (
fk_bonus INTEGER NOT NULL,
fk_subject INTEGER NOT NULL,

PRIMARY KEY (fk_bonus, fk_subject),
FOREIGN KEY(fk_bonus) REFERENCES bonuses(pk_bonus),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

CREATE TABLE invested_money (
pk_invested_money INTEGER PRIMARY KEY NOT NULL,
fk_investor INTEGER NOT NULL,
fk_currency INTEGER NOT NULL,

date TEXT,
short_name TEXT,
description TEXT,
comment TEXT,
amount REAL,

FOREIGN KEY(fk_investor) REFERENCES investors(pk_investor),
FOREIGN KEY(fk_currency) REFERENCES currencies(pk_currency),
UNIQUE(pk_invested_money)
);

CREATE TABLE invested_money_subjects_link (
fk_invested_money INTEGER NOT NULL,
fk_subject INTEGER NOT NULL,

PRIMARY KEY (fk_invested_money, fk_subject),
FOREIGN KEY(fk_invested_money) REFERENCES invested_money(pk_invested_money),
FOREIGN KEY(fk_subject) REFERENCES subjects(pk_subject)
);

