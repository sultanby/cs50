import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("Email") or not request.form.get("age") or not request.form.get("Gender") or not request.form.get("EducationInput") or not request.form.get("Area"):
        return render_template("error.html")

    with open("survey.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames=["Email", "age", "Gender", "EducationInput", "Area"])
        writer.writerow({"Email": request.form.get("Email"), "age": request.form.get("age"), "Gender": request.form.get("Gender"),
                         "EducationInput": request.form.get("EducationInput"), "Area": request.form.get("Area")})
    #file = open("survey.csv", "a")
    #writer = csv.writer(file)
    #writer.writerow((request.form.get("Email"), request.form.get("age"), request.form.get("Gender"), request.form.get("EducationInput"), request.form.get("Area")))
    # file.close()
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    submits2 = []
    with open("./survey.csv", "r") as file:
        reader = csv.reader(file)
        for row in reader:
            submits2.append(row)
        ##data = list(reader)
    #file = open("survey.csv", "r")
    #reader = csv.reader(file)
    #data = list(reader)
    return render_template("sheet1.html", submits=submits2)

    # data=data)

    # return render_template("error.html", message="TODO now")
