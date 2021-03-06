/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "MateriaEditor.h"

MateriaEditor::MateriaEditor(qreal Scale,QWidget *parent):QWidget(parent)
{
	scale=Scale;
	init_display();
	init_data();
	init_connections();
	setMateria(FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);//Smallest Possible Size. ready for use now.
}
MateriaEditor::MateriaEditor(quint8 materia_id,qint32 materia_ap,qreal Scale,QWidget *parent):QWidget(parent)
{
	scale=Scale;
	init_display();
	init_data();
	init_connections();
	setMateria(materia_id,materia_ap);
}
void MateriaEditor::init_display()
{//Make Widgets and set Properties.
	//Widget Creation.
	combo_type =new QComboBox;
	combo_materia = new QComboBox;
	sb_ap = new QSpinBox;
	lbl_slash = new QLabel("/");
	lbl_max_ap = new QLabel;
	btn_rm_materia = new QPushButton;
	btn_rm_materia->setShortcut(QKeySequence::Delete);
	btn_copy_materia = new QPushButton;
	btn_copy_materia->setShortcut(QKeySequence::Copy);
	btn_paste_materia = new QPushButton;
	btn_paste_materia->setShortcut(QKeySequence::Paste);
	box_stars = new QFrame;
	btn_star1 = new QPushButton;
	btn_star2 = new QPushButton;
	btn_star3 = new QPushButton;
	btn_star4 = new QPushButton;
	btn_star5 = new QPushButton;
	eskill_list = new QListWidget;
	box_skills = new QGroupBox;
	list_skills = new QListWidget;
	box_stats = new QGroupBox;
	lbl_stats = new QLabel;
	btn_clear_eskills = new QPushButton;
	btn_master_eskills = new QPushButton;
	eskill_group = new QGroupBox;
	eskill_group->setMinimumHeight(150);
	list_status = new QListWidget;
	box_status_effects = new QGroupBox;
	frm_name_type =new QFrame;
	frm_ap = new QFrame;
	frm_ap_stars = new QFrame;
	lbl_materiaIcon = new QLabel;
	lbl_materiaName= new QLabel;
	v_spacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
	//Special Properties Of Above Widgets
	sb_ap->setWrapping(1);
	sb_ap->setAlignment(Qt::AlignCenter);
	btn_rm_materia->setIcon(QIcon::fromTheme(QString("edit-clear"),QPixmap(":/common/edit-clear")));
	btn_copy_materia->setIcon(QIcon::fromTheme(QString("edit-copy"),QPixmap(":/common/edit-copy")));
	btn_paste_materia->setIcon(QIcon::fromTheme(QString("edit-paste"),QPixmap(":/common/edit-paste")));

	QString style=QString("QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:rgba(%1,%2,%3,96);}").arg(QString::number(this->palette().highlight().color().red()),QString::number(this->palette().highlight().color().green()),QString::number(this->palette().highlight().color().blue()));
	btn_star1->setStyleSheet(style);
	btn_star2->setStyleSheet(style);
	btn_star3->setStyleSheet(style);
	btn_star4->setStyleSheet(style);
	btn_star5->setStyleSheet(style);
	btn_star1->setFlat(true);
	btn_star2->setFlat(true);
	btn_star3->setFlat(true);
	btn_star4->setFlat(true);
	btn_star5->setFlat(true);
	//Set Label Text
	lbl_slash->setText("/");
	btn_clear_eskills->setText(tr("Clear"));
	btn_master_eskills->setText(tr("Master"));
	box_skills->setTitle(tr("Skills"));
	box_stats->setTitle(tr("Stat Changes"));
	btn_rm_materia->setToolTip(tr("Delete"));
	btn_rm_materia->setStyleSheet(style);
	btn_rm_materia->setFlat(true);
	btn_copy_materia->setToolTip(tr("Copy"));
	btn_copy_materia->setStyleSheet(style);
	btn_copy_materia->setFlat(true);
	btn_paste_materia->setToolTip(tr("Paste"));
	btn_paste_materia->setStyleSheet(style);
	btn_paste_materia->setFlat(true);
	box_status_effects->setTitle(tr("Added Effect"));
	//set Hidden
	eskill_group->setHidden(true);
	box_status_effects->setHidden(true);
	box_stats->setHidden(true);

	//set Minimum Sizes.
	btn_copy_materia->setFixedSize(24*scale,24*scale);
	btn_paste_materia->setFixedSize(24*scale,24*scale);
	btn_rm_materia->setFixedSize(24*scale,24*scale);
	lbl_materiaIcon->setFixedSize(24*scale,24*scale);
	combo_type->setMinimumHeight(24*scale);
	combo_materia->setMinimumHeight(24*scale);

	list_skills->addItem(new QListWidgetItem("Item"));
	list_skills->setFixedHeight(list_skills->sizeHintForRow(0)*5 +list_skills->contentsMargins().top()+ list_skills->contentsMargins().bottom()+3);
	list_skills->setSelectionMode(QAbstractItemView::NoSelection);
	list_status->setFixedHeight(list_skills->height());
	list_status->setSelectionMode(QAbstractItemView::NoSelection);

	//size policies
	combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
	combo_type->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    sb_ap->setMinimumWidth(fontMetrics().width(QChar('W'))*7);
	sb_ap->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
	btn_rm_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
	btn_copy_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
	btn_paste_materia->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
	box_stats->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
	frm_ap->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
	box_status_effects->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);

//Set up display
	this->setContentsMargins(0,0,0,0);
	QHBoxLayout * type_name_layout = new QHBoxLayout;
	type_name_layout->addWidget(lbl_materiaIcon);
	type_name_layout->addWidget(lbl_materiaName);
	type_name_layout->addWidget(combo_type);
	type_name_layout->addWidget(combo_materia);
	type_name_layout->addWidget(btn_copy_materia);
	type_name_layout->addWidget(btn_paste_materia);
	type_name_layout->addWidget(btn_rm_materia);
	type_name_layout->setContentsMargins(3,0,0,0);

	QHBoxLayout * ap_layout = new QHBoxLayout;
	ap_layout->addWidget(sb_ap);
	ap_layout->addWidget(lbl_slash);
	lbl_slash->setFixedWidth(this->font().pointSize());
	ap_layout->addWidget(lbl_max_ap);
	ap_layout->setContentsMargins(0,0,0,0);
	frm_ap->setLayout(ap_layout);

	frm_name_type->setLayout(type_name_layout);

	QHBoxLayout *stars = new QHBoxLayout;
	stars->setContentsMargins(3,0,0,0);
	stars->addWidget(btn_star1);
	stars->addWidget(btn_star2);
	stars->addWidget(btn_star3);
	stars->addWidget(btn_star4);
	stars->addWidget(btn_star5);
	QSpacerItem *spacer2 = new QSpacerItem(30,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
	stars->addSpacerItem(spacer2);
	box_stars->setLayout(stars);

	/* Init Skills Area */
	ap_stars_layout =  new QGridLayout;
	ap_stars_layout->setContentsMargins(0,0,0,0);
	ap_stars_layout->addWidget(box_stars,0,0,1,1,0);
	ap_stars_layout->addWidget(frm_ap,0,1,1,1,0);

	frm_ap_stars->setLayout(ap_stars_layout);
	frm_ap_stars->setContentsMargins(0,0,0,0);

	QHBoxLayout *low_eskill_layout = new QHBoxLayout;
	low_eskill_layout->setContentsMargins(0,0,0,0);
	low_eskill_layout->addWidget(btn_master_eskills);
	low_eskill_layout->addWidget(btn_clear_eskills);

	QVBoxLayout * eskill_layout = new QVBoxLayout;
	eskill_layout->addWidget(eskill_list);
	eskill_layout->addItem(low_eskill_layout);
	eskill_layout->setContentsMargins(0,0,0,0);
	eskill_layout->setSpacing(0);
	eskill_group->setLayout(eskill_layout);

	QVBoxLayout *skill_layout = new QVBoxLayout;
	skill_layout->addWidget(list_skills);
	skill_layout->addWidget(eskill_group);

	box_skills->setLayout(skill_layout);
	skill_layout->setContentsMargins(3,0,0,0);
	skill_layout->setSpacing(2);

	QHBoxLayout *stat_layout = new QHBoxLayout;
	stat_layout->setContentsMargins(3,0,0,0);
	stat_layout->addWidget(lbl_stats);
	box_stats->setLayout(stat_layout);

	QHBoxLayout * status_effect_layout = new QHBoxLayout;
	status_effect_layout->addWidget(list_status);
	status_effect_layout->setContentsMargins(3,0,0,0);
	box_status_effects->setLayout(status_effect_layout);

	QHBoxLayout *skill_status_layout = new QHBoxLayout;
	skill_status_layout->setContentsMargins(0,0,0,0);
	skill_status_layout->addWidget(box_skills);
	skill_status_layout->addWidget(box_status_effects);

	frm_skill_status = new QFrame;
	frm_skill_status->setContentsMargins(0,0,0,0);
	frm_skill_status->setLayout(skill_status_layout);
	frm_skill_status->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(3,0,0,0);
	main_layout->setSpacing(2);
	main_layout->addWidget(frm_name_type);
	main_layout->addWidget(frm_ap_stars);
	main_layout->addWidget(frm_skill_status);
	main_layout->addWidget(box_stats);

	QVBoxLayout *Final = new QVBoxLayout(this);
	Final->setSpacing(0);
	Final->addLayout(main_layout);
	Final->addSpacerItem(v_spacer);
	Final->setContentsMargins(6,6,6,0);
	this->setLayout(Final);
}

void MateriaEditor::init_connections(void)
{
	connect(btn_star1,SIGNAL(clicked()),this,SLOT(btn_star1_clicked()));
	connect(btn_star2,SIGNAL(clicked()),this,SLOT(btn_star2_clicked()));
	connect(btn_star3,SIGNAL(clicked()),this,SLOT(btn_star3_clicked()));
	connect(btn_star4,SIGNAL(clicked()),this,SLOT(btn_star4_clicked()));
	connect(btn_star5,SIGNAL(clicked()),this,SLOT(btn_star5_clicked()));
	connect(btn_rm_materia,SIGNAL(clicked()),this,SLOT(remove_materia()));
	connect(btn_copy_materia,SIGNAL(clicked()),this,SLOT(copy_materia()));
	connect(btn_paste_materia,SIGNAL(clicked()),this,SLOT(paste_materia()));
	connect(sb_ap,SIGNAL(valueChanged(int)),this,SLOT(sb_ap_changed(int)));
	connect(combo_type,SIGNAL(currentIndexChanged(int)),this,SLOT(type_changed(int)));
	connect(eskill_list,SIGNAL(clicked(QModelIndex)),this,SLOT(eskill_list_clicked(QModelIndex)));
	connect(combo_materia,SIGNAL(currentIndexChanged(QString)),this,SLOT(materia_changed(QString)));
	connect(btn_master_eskills,SIGNAL(clicked()),this,SLOT(btn_master_eskill_clicked()));
	connect(btn_clear_eskills,SIGNAL(clicked()),this,SLOT(btn_clear_eskill_clicked()));
}
void MateriaEditor::init_data()
{
	data = new FF7Materia;
	//Fill Eskill List.
	for(int i=0;i<24;i++)
	{
		QListWidgetItem *newItem = new QListWidgetItem();
		newItem->setText(data->enemySkill(i));
		newItem->setCheckState(Qt::Unchecked);
		eskill_list->addItem(newItem);
	}
	QString style=QString("QListView::indicator:unchecked {image: url(:/materia/command_star_empty);} QListView::indicator:checked{image: url(:/materia/command_star_full);}");
	eskill_list->setStyleSheet(style);
	eskill_list->setMaximumHeight(eskill_list->sizeHintForRow(0)*24 +eskill_list->contentsMargins().top() + eskill_list->contentsMargins().bottom());
	eskill_list->setSelectionMode(QAbstractItemView::NoSelection);
	//Fill Combo_type
	combo_type->addItem(data->iconAllMateria(),tr("All Materia"));
	combo_type->addItem(data->icon(FF7Materia::MasterMagic),tr("Magic"));
	combo_type->addItem(data->icon(FF7Materia::MasterSummon),tr("Summon"));
	combo_type->addItem(data->icon(FF7Materia::Underwater),tr("Independent"));
	combo_type->addItem(data->icon(FF7Materia::StealAsWell),tr("Support"));
	combo_type->addItem(data->icon(FF7Materia::MasterCommand),tr("Command"));

	//Set initial combo_materia info.
	for(int i=0;i<91;i++)
	{
		if(data->name(i) !="DON'T USE"){combo_materia->addItem(data->icon(i),data->name(i));}
	}
	_id=0;
	_current_ap=0;
	buffer_id=0;
	buffer_ap=0;
	editable=true;
	lbl_materiaIcon->setHidden(editable);
	lbl_materiaName->setHidden(editable);
}

void MateriaEditor::setMateria(quint8 materia_id,qint32 materia_ap)
{
	if (materia_id <91)
	{//valid Materia..
		if(_id != materia_id)
		{
			_id = materia_id;
			sb_ap->setEnabled(1);
			emit id_changed(_id);
		 }
	}
	else
	{//Invalid Data Reset Materia.
		if(_id != FF7Materia::EmptyId){emit id_changed(FF7Materia::EmptyId);}
		_id=FF7Materia::EmptyId;
		sb_ap->setEnabled(0);
		sb_ap->setValue(FF7Materia::MaxMateriaAp);
		_current_ap = FF7Materia::MaxMateriaAp;//set since setAp ingores the 0xFF id.
		box_status_effects->setHidden(true);
		box_stats->setHidden(true);
	}
	this->setName();
	this->setAP(materia_ap);
	this->setStats();


}
void MateriaEditor::setAP(qint32 ap)
{
	sb_ap->setMaximum(MaxAP());
	lbl_max_ap->setText(QString(" %1").arg(QString::number(MaxAP())));

	if( (_id ==FF7Materia::Underwater) || (_id==FF7Materia::MasterCommand) || (_id==FF7Materia::MasterMagic) ||(_id==FF7Materia::MasterSummon) ||(_id==FF7Materia::EnemySkill))
	{
		frm_ap_stars->setHidden(true);
		if(_current_ap != ap){_current_ap = ap; emit(ap_changed(_current_ap));}
		if(_id==FF7Materia::EnemySkill)
		{//Eskill Materia Specialness.
			for (int i=0;i<24;i++)
			{
				if (_current_ap & (1 << i)){eskill_list->item(i)->setCheckState(Qt::Checked);}
				else{eskill_list->item(i)->setCheckState(Qt::Unchecked);}
			}
		}
	}
	else if(_id ==FF7Materia::EmptyId)
	{
		frm_ap_stars->setHidden(true);
		lbl_max_ap->setText("");
	}
	else
	{//All Other Materia
		frm_ap_stars->setHidden(false);
		if( (ap <FF7Materia::MaxMateriaAp) && (ap< data->ap(_id,data->levels(_id)-1)) )
		{
			_current_ap = ap;
			sb_ap->setValue(_current_ap);
		}
		else
		{
			_current_ap = FF7Materia::MaxMateriaAp;
			sb_ap->setValue(data->ap(_id,data->levels(_id)-1));
		}
		emit ap_changed(_current_ap);
	}
	setLevel();
}

void MateriaEditor::setName()
{
	if(_id==FF7Materia::EmptyId){combo_type->setCurrentIndex(0);combo_materia->setCurrentIndex(-1);lbl_materiaName->clear();lbl_materiaIcon->setPixmap(QPixmap());}
	else
	{
		lbl_materiaIcon->setPixmap(QPixmap::fromImage(data->image(_id)).scaled(lbl_materiaIcon->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		lbl_materiaName->setText(data->name(_id));
		if(combo_type->currentIndex()!=FF7Materia::Unknown){combo_type->setCurrentIndex(data->type(_id));}
		for(int i=0;i<combo_materia->count();i++)
		{//loop thru type and see if name matches if so set index and stop
			if(data->name(_id) == combo_materia->itemText(i)){combo_materia->setCurrentIndex(i);return;}
		}
	}
}

void MateriaEditor::setStats()
{
	list_status->clear();
	lbl_stats->clear();
	QString title = tr("Skills");
	if(_id !=FF7Materia::EmptyId)
	{
		if(data->element(_id)!="")
		{
			title.append("-");
			title.append(data->element(_id));
		}
		if(data->statString(_id)!="")
		{
			lbl_stats->setText(data->statString(_id));
			box_stats->setHidden(false);
		}
		else{box_stats->setHidden(true);}
		if(data->status(_id).at(0).toLocal8Bit() !="")
		{
			list_status->addItems(data->status(_id));
			box_status_effects->setFixedWidth(this->width()/3);
			box_status_effects->setHidden(false);
		}
		else{box_status_effects->setHidden(true);}
		box_skills->setTitle(title);
	}
}
void MateriaEditor::setLevel()
{
	_level=0;
	if( _id==FF7Materia::EmptyId){/*catch to avoid CID 25848*/ }
	else if( (_id==FF7Materia::EnemySkill)||(_id==FF7Materia::Underwater)||(_id==FF7Materia::MasterCommand)||(_id==FF7Materia::MasterMagic)||(_id==FF7Materia::MasterSummon)){_level=1;}
	else{for(int i=0;i<data->levels(_id);i++){if(_current_ap >= data->ap(_id,i)){_level++;}}}
	setStars();
	setSkills();
}

void MateriaEditor::setStars()
{
   //Hide if its eskill Materia
	if((_id==FF7Materia::EnemySkill)||(_id==FF7Materia::Underwater)||(_id==FF7Materia::MasterCommand)||(_id==FF7Materia::MasterMagic)||(_id==FF7Materia::MasterSummon)||(_id==FF7Materia::EmptyId)){box_stars->setHidden(true);return;}
	else
	{
		box_stars->setHidden(false);
		btn_star1->setHidden(true);
		btn_star2->setHidden(true);
		btn_star3->setHidden(true);
		btn_star4->setHidden(true);
		btn_star5->setHidden(true);
		if(data->type(_id) !=0)
		{
			btn_star1->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(btn_star1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			btn_star2->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(btn_star2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			btn_star3->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(btn_star3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			btn_star4->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(btn_star4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			btn_star5->setIcon(QPixmap::fromImage(data->imageEmptyStar(_id)).scaled(btn_star5->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		}
		switch(_level)
		{//no break on purpose
			case 5: btn_star5->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_star5->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			case 4: btn_star4->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_star4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			case 3: btn_star3->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_star3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			case 2: btn_star2->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_star2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
			case 1: btn_star1->setIcon(QPixmap::fromImage(data->imageFullStar(_id)).scaled(btn_star1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		};
		switch(data->levels(_id))
		{//no break on purpose.
			case 5: btn_star5->setHidden(false);
			case 4: btn_star4->setHidden(false);
			case 3: btn_star3->setHidden(false);
			case 2: btn_star2->setHidden(false);
			case 1: btn_star1->setHidden(false);
		};
	}
}

void MateriaEditor::setSkills()
{
	list_skills->clear();
	if( _id ==FF7Materia::EnemySkill)
	{
		box_skills->setHidden(false);
		list_skills->setHidden(true);
		eskill_group->setHidden(false);
		frm_skill_status->adjustSize();
		v_spacer->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
		v_spacer->invalidate();
	}
	else if(_id ==FF7Materia::EmptyId)
	{
		box_skills->setHidden(true);
		list_skills->setHidden(true);
		eskill_group->setHidden(true);
		v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
		v_spacer->invalidate();
	}
	else
	{
		box_skills->setHidden(false);
		list_skills->setHidden(false);
		eskill_group->setHidden(true);
		v_spacer->changeSize(0,0,QSizePolicy::Preferred,QSizePolicy::Expanding);
		v_spacer->invalidate();
		switch (_level)
		{// no breaks on purpose
			case 5:if(data->skills(_id).count()>4){list_skills->insertItem(0,data->skills(_id).at(4));}
			case 4:if(data->skills(_id).count()>3){list_skills->insertItem(0,data->skills(_id).at(3));}
			case 3:if(data->skills(_id).count()>2){list_skills->insertItem(0,data->skills(_id).at(2));}
			case 2:if(data->skills(_id).count()>1){list_skills->insertItem(0,data->skills(_id).at(1));}
			case 1:if(data->skills(_id).count()>0){list_skills->insertItem(0,data->skills(_id).at(0));}
		}
		//frm_skill_status->adjustSize();
	}
	this->layout()->update();
}

void MateriaEditor::btn_star1_clicked(){setAP(data->ap(_id,0));setLevel();}
void MateriaEditor::btn_star2_clicked(){setAP(data->ap(_id,1));setLevel();}
void MateriaEditor::btn_star3_clicked(){setAP(data->ap(_id,2));setLevel();}
void MateriaEditor::btn_star4_clicked(){setAP(data->ap(_id,3));setLevel();}
void MateriaEditor::btn_star5_clicked(){setAP(FF7Materia::MaxMateriaAp);setLevel();}

void MateriaEditor::materia_changed(QString new_name)
{
	for(int i=0;i<91;i++)
	{
		if(data->name(i)==new_name){if(_id != i){setMateria(i,_current_ap);}return;}
	}
}

void MateriaEditor::type_changed(int new_type)
{
	combo_materia->clear();
	combo_materia->blockSignals(1);
	if(new_type ==0)for(int i=0;i<91;i++){if(data->name(i) !="DON'T USE"){combo_materia->addItem(data->icon(i),data->name(i));}}
	else{for(int i=0;i<91;i++){if(data->type(i) == new_type){combo_materia->addItem(data->icon(i),data->name(i));}}}
	//look for the current id in the new list if found set it other wise set index -1
	if(_id !=FF7Materia::EmptyId){combo_materia->setCurrentIndex(combo_materia->findText(data->name(_id)));}

	else{combo_materia->setCurrentIndex(-1);}
	combo_materia->blockSignals(0);
}

qint32 MateriaEditor::ap(void){return _current_ap;}
qint8 MateriaEditor::id(void){return _id;}
void MateriaEditor::sb_ap_changed(qint32 ap){setAP(ap);}

void MateriaEditor::eskill_list_clicked(QModelIndex index)
{
	int i = index.row();
	if (eskill_list->item(i)->checkState() == Qt::Checked){_current_ap |= (1<<i);}
	else{_current_ap &= ~(1<<i);}
	emit(ap_changed(_current_ap));
}
qint32 MateriaEditor::MaxAP(void)
{
	if( (_id==FF7Materia::Underwater) || (_id ==FF7Materia::MasterCommand) || (_id==FF7Materia::MasterMagic) ||(_id==FF7Materia::MasterSummon) || (_id==FF7Materia::EnemySkill))
	{
		return FF7Materia::MaxMateriaAp;
	}
	else{return data->ap(_id,data->levels(_id)-1);}
}

void MateriaEditor::remove_materia(void){setMateria(FF7Materia::EmptyId,FF7Materia::MaxMateriaAp);}
void MateriaEditor::copy_materia(){buffer_id= _id; buffer_ap = _current_ap;}
void MateriaEditor::paste_materia(){setMateria(buffer_id,buffer_ap);}
void MateriaEditor::btn_clear_eskill_clicked(){if(_current_ap!=0){setAP(0);}}
void MateriaEditor::btn_master_eskill_clicked(){if(_current_ap != FF7Materia::MaxMateriaAp){setAP(FF7Materia::MaxMateriaAp);}}

void MateriaEditor::setStarsSize(int size)
{

	btn_star1->setFixedSize(size,size);
	btn_star2->setFixedSize(size,size);
	btn_star3->setFixedSize(size,size);
	btn_star4->setFixedSize(size,size);
	btn_star5->setFixedSize(size,size);
	btn_star1->setIconSize(QSize(size,size));
	btn_star2->setIconSize(QSize(size,size));
	btn_star3->setIconSize(QSize(size,size));
	btn_star4->setIconSize(QSize(size,size));
	btn_star5->setIconSize(QSize(size,size));
	box_stars->setFixedHeight(size +(size/8));
	setStars();
	box_stars->adjustSize();

	frm_ap_stars->layout()->removeWidget(box_stars);
	frm_ap_stars->layout()->removeWidget(frm_ap);

	if(size<=32*scale)
	{
	ap_stars_layout->addWidget(box_stars,0,0,1,1,0);
		ap_stars_layout->addWidget(frm_ap,0,1,1,1,0);
		if(box_stars->sizeHint().height() < frm_ap->sizeHint().height())
		{
			frm_ap_stars->setFixedHeight(frm_ap->sizeHint().height()+6);
		}
		else{frm_ap_stars->setFixedHeight(box_stars->sizeHint().height()+6);}
	}
	else
	{
		ap_stars_layout->addWidget(frm_ap,0,0,1,1,0);
		ap_stars_layout->addWidget(box_stars,1,0,1,1,0);
		frm_ap_stars->setFixedHeight( (size +(size/6)) + (frm_ap->sizeHint().height()+6) );
	}
	frm_ap_stars->adjustSize();
}
bool MateriaEditor::isEditable(void){return editable;}
void MateriaEditor::setEditable(bool edit)
{
	editable = edit;
	editMode();
}
void MateriaEditor::editMode(void)
{
	//Set blockSignals = !editable.
	btn_star1->blockSignals(!editable);
	btn_star2->blockSignals(!editable);
	btn_star3->blockSignals(!editable);
	btn_star4->blockSignals(!editable);
	btn_star5->blockSignals(!editable);
	//Set Enabled = editable
	if(_id != FF7Materia::EmptyId){sb_ap->setEnabled(editable);}
	btn_paste_materia->setHidden(!editable);
	btn_rm_materia->setHidden(!editable);
	combo_materia->setHidden(!editable);
	combo_type->setHidden(!editable);
	//show the materia Icon and Name if not hidden.
	lbl_materiaIcon->setHidden(editable);
	lbl_materiaName->setHidden(editable);
	btn_master_eskills->setHidden(!editable);
	btn_clear_eskills->setHidden(!editable);
	if(editable)
	{
		for(int i=0;i<eskill_list->count();i++)
		{
			eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() |= Qt::ItemIsUserCheckable);
		}
	}
   else
   {
	   for(int i=0;i<eskill_list->count();i++)
	   {
		   eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() &=~Qt::ItemIsUserCheckable);
	   }
   }

}
void MateriaEditor::setHoverStyle(QString hoverColor)
{
		QString style=QString("QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color:%1}").arg(hoverColor);
		btn_rm_materia->setStyleSheet(style);
		btn_copy_materia->setStyleSheet(style);
		btn_paste_materia->setStyleSheet(style);
		btn_star1->setStyleSheet(style);
		btn_star2->setStyleSheet(style);
		btn_star3->setStyleSheet(style);
		btn_star4->setStyleSheet(style);
		btn_star5->setStyleSheet(style);
}
void MateriaEditor::setEditableMateriaCombo(bool enabled)
{
	combo_materia->setEditable(enabled);
	combo_materia->setInsertPolicy(QComboBox::NoInsert);
}
